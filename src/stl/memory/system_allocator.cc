#include "system_allocator.h"

#include <cstdlib>

//address+offset should be aligned, NOT address itself
void* stl::system_allocator::allocate(size_t size, size_t align, size_t offset)
{
    return ::malloc(size);
}

void stl::system_allocator::free(void* object)
{
    ::free(object);
}