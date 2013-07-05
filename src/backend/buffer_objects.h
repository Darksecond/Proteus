#pragma once

#include "util/generic_handle.h"

namespace backend
{
    typedef generic_handle<12, 20> vertex_buffer_handle;
    typedef generic_handle<12, 20> index_buffer_handle;
    
    /**
     * Format of the indexes in the index buffer.
     */
    enum class index_format : uint32_t
    {
        UINT = sizeof(uint32_t),
        USHORT = sizeof(uint16_t),
        UBYTE = sizeof(uint8_t),
    };
    
    /**
     * Create a new vertex buffer.
     * \param data data to load into vertex buffer.
     * \param size size of data in bytes.
     * \return handle to the created buffer.
     * will invalid if there are no more buffers available.
     */
    //TODO replace size with count and stride?
    vertex_buffer_handle create_vertex_buffer(uint32_t size, const void* data);
    
    /**
     * Destroy a vertex buffer from a handle.
     * Will assert when the handle is invalid.
     */
    void destroy_vertex_buffer(vertex_buffer_handle handle);
    
    //TODO access_vertex_buffer(handle)
    //TODO create_dynamic_vertex_buffer
    
    /**
     * Create a new index buffer.
     * \param count amount of indices.
     * \param format format of the indices.
     * \param data the indices to load.
     * \return handle to the created buffer.
     * will assert when there are no more free buffers available.
     */
    index_buffer_handle create_index_buffer(uint32_t count, index_format format,
                                            const void* data);
    
    /**
     * destroy an index buffer from a handle.
     * Will assert if handle is invalid.
     */
    void destroy_index_buffer(index_buffer_handle handle);
    
    //TODO access_index_buffer
};