#pragma once

namespace STL
{
    class Arena
    {
        virtual ~Arena() {}
        virtual void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const STL::SourceInfo& info) = 0;
        virtual void free(void* object, const STL::SourceInfo& info) = 0;
    };
};