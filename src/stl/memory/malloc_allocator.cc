#include "malloc_allocator.h"

#include <cstdlib>

//address+offset should be aligned, NOT address itself
void* stl::malloc_allocator::allocate(size_t size, size_t align, size_t offset, const stl::source_info& info)
{
    return ::malloc(size);
}

void stl::malloc_allocator::free(void* object, const stl::source_info& info)
{
    ::free(object);
}