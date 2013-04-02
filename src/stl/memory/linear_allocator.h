#pragma once

#include "types.h"
#include "log.h"

namespace stl
{
    class linear_allocator
    {
        uint8_t* _start;
        uint8_t* _end;
        uint8_t* _current;
    public:
        linear_allocator(const void* start, const void* end);
        
        //address+offset should be aligned, NOT address itself
        void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const stl::source_info& info);
        void free(void* object, const stl::source_info& info);
        inline void reset() { _current = _start; }
    };
};