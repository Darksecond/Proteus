#include "mesh_library.h"

#include "backend/buffer_objects.h"

#include <cassert>

using namespace graphics;

mesh_library::mesh_library(stl::arena* temporary, stl::arena* permanent) : _permanent_arena(permanent), _temporary_arena(temporary)
{
    assert(temporary);
    assert(permanent);
}

void mesh_library::on_load(uint32_t fourCC, stl::string_hash name, stl::file* file)
{
    assert(fourCC == get_chunk_4CC());
    
    //header;
    //file->read(header);
    
    /*
     
    const int vertex_data_size = 4096; //TODO read, or calculate from header instead
     
    //load vertices
    char* vertex_data = P_NEW_ARRAY(*_temporary_arena, char[vertex_data_size]);
    file->read(vertex_data, vertex_data_size);
    backend::vertex_buffer_handle vertex_buffer = backend::create_vertex_buffer(vertex_data_size, vertex_data);
    P_DELETE_ARRAY(*_temporary_arena, vertex_data);
     
    */
    
    //load indexes
    
    //TODO create and store a 'Mesh' struct
}

uint32_t mesh_library::get_chunk_4CC()
{
    return 'MESH';
}
