#pragma once

#include "util/generic_handle.h"

namespace graphics
{
    namespace backend
    {
        typedef generic_handle<12, 20> vertex_buffer_handle;
        typedef generic_handle<12, 20> index_buffer_handle;
        
        enum class index_format : uint32_t
        {
            UINT = sizeof(uint32_t),
            USHORT = sizeof(uint16_t),
            UBYTE = sizeof(uint8_t),
        };
        
        vertex_buffer_handle create_vertex_buffer(uint32_t size, const void* data);
        void destroy_vertex_buffer(vertex_buffer_handle handle);
        //access_vertex_buffer
        
        index_buffer_handle create_index_buffer(uint32_t count, index_format format,
                                                const void* data);
        void destroy_index_buffer(index_buffer_handle handle);
        //access_index_buffer
    };
};