#pragma once

namespace stl
{
    class Arena
    {
        virtual ~Arena() {}
        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const SourceInfo& info) = 0;
        virtual void free(void* object, const SourceInfo& info) = 0;
    };
};