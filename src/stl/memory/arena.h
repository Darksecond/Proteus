#pragma once

#include "stl/types.h"
#include "stl/logging/log.h"

namespace stl
{
    class arena
    {
    public:
        virtual ~arena() {}
        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const source_info& info) = 0;
        virtual void free(void* object, const source_info& info) = 0;
    };
};