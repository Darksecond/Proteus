#include "MallocAllocator.h"

#include <cstdlib>

//address+offset should be aligned, NOT address itself
void* STL::MallocAllocator::allocate(size_t size, size_t align, size_t offset, const STL::SourceInfo& info)
{
    return ::malloc(size);
}

void STL::MallocAllocator::free(void* object, const STL::SourceInfo& info)
{
    ::free(object);
}