#pragma once

#include "types.h"
#include "stl/logging/log.h"

namespace stl
{
    class system_allocator
    {
    public:
        //address+offset should be aligned, NOT address itself
        void* allocate(size_t size, size_t align, size_t offset);
        void free(void* object);
    };
};