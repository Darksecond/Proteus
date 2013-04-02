#include "linear_allocator.h"

#include "new_delete.h"
#include "types.h"

stl::linear_allocator::linear_allocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* stl::linear_allocator::allocate(const size_t size, const size_t alignment, const size_t alignment_offset, const stl::source_info& info)
{
    _current = (uint8_t*)memory_internals::align_forward(_current + alignment_offset, alignment) - alignment_offset;
    void* ptr = _current;
    _current += size;
    if(_current > _end)
    {
        return nullptr;
    }
    
    return ptr;
}

void stl::linear_allocator::free(void* object, const stl::source_info& info)
{
}