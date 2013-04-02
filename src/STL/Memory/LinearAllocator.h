#pragma once

#include "types.h"
#include "log.h"

namespace STL
{
    class LinearAllocator
    {
        uint8_t* _start;
        uint8_t* _end;
        uint8_t* _current;
    public:
        LinearAllocator(const void* start, const void* end);
        
        //address+offset should be aligned, NOT address itself
        void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const STL::SourceInfo& info);
        void free(void* object, const STL::SourceInfo& info);
        inline void reset() { _current = _start; }
    };
};