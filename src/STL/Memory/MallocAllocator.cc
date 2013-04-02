#include "MallocAllocator.h"

#include <cstdlib>

//address+offset should be aligned, NOT address itself
void* stl::MallocAllocator::allocate(size_t size, size_t align, size_t offset, const stl::SourceInfo& info)
{
    return ::malloc(size);
}

void stl::MallocAllocator::free(void* object, const stl::SourceInfo& info)
{
    ::free(object);
}