#pragma once

#include "types.h"
#include "log.h"

namespace stl
{
    class MallocAllocator
    {
    public:
        //address+offset should be aligned, NOT address itself
        void* allocate(size_t size, size_t align, size_t offset, const SourceInfo& info);
        void free(void* object, const SourceInfo& info);
    };
};