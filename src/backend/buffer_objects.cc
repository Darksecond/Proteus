#include "buffer_objects.h"

#include "opengl.h"

#include "stl/containers/fixed_array.h"

#include <cassert>

static constexpr int _vertex_buffer_amount = 4096;
static constexpr int _index_buffer_amount = 4096;

static stl::fixed_array<GLuint, _vertex_buffer_amount> _vertex_buffers;
static stl::fixed_array<uint32_t, _vertex_buffer_amount> _vertex_buffer_generations;

static stl::fixed_array<GLuint, _index_buffer_amount> _index_buffers;
static stl::fixed_array<uint32_t, _index_buffer_amount> _index_buffer_generations;

//TODO save count and stride for later retreival?
backend::vertex_buffer_handle backend::create_vertex_buffer(uint32_t count, uint32_t stride, const void* data)
{
    assert(data);
    assert(count > 0);
    assert(stride > 0);
    
    uint32_t size = count * stride;
    
    for(unsigned i = 0; i < _vertex_buffer_amount; ++i)
    {
        if(_vertex_buffers[i] == 0)
        {
            glGenBuffers(1, &_vertex_buffers[i]);
            glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffers[i]);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            return vertex_buffer_handle{i, _vertex_buffer_generations[i]};
        }
    }
    //TODO assert or return invalid handle
    assert(false);
}

void backend::destroy_vertex_buffer(vertex_buffer_handle handle)
{
    assert(handle.generation == _vertex_buffer_generations[handle.index]);
    
    glDeleteBuffers(1, &_vertex_buffers[handle.index]);
    _vertex_buffers[handle.index] = 0;
    ++_vertex_buffer_generations[handle.index];
}

backend::index_buffer_handle backend::create_index_buffer(uint32_t count, index_format format, const void* data)
{
    assert(data);
    assert(count > 0);
    
    uint32_t size = static_cast<uint32_t>(format) * count;
    for(unsigned i = 0; i < _index_buffer_amount; ++i)
    {
        if(_index_buffers[i] == 0)
        {
            glGenBuffers(1, &_index_buffers[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffers[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            return index_buffer_handle{i, _index_buffer_generations[i]};
        }
    }
    //TODO assert or return invalid handle
    assert(false);
}

void backend::destroy_index_buffer(index_buffer_handle handle)
{
    assert(handle.generation == _index_buffer_generations[handle.index]);
    
    glDeleteBuffers(1, &_index_buffers[handle.index]);
    _index_buffers[handle.index] = 0;
    ++_index_buffer_generations[handle.index];
}
