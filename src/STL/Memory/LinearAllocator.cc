#include "LinearAllocator.h"
#include "NewDelete.h"
#include "types.h"

STL::LinearAllocator::LinearAllocator(const void* start, const void* end) : _start((uint8_t*)start), _end((uint8_t*)end), _current(_start)
{
}

void* STL::LinearAllocator::allocate(const size_t size, const size_t alignment, const size_t alignment_offset, const STL::SourceInfo& info)
{
    _current = (uint8_t*)MemoryInternals::align_forward(_current + alignment_offset, alignment) - alignment_offset;
    void* ptr = _current;
    _current += size;
    if(_current > _end)
    {
        return nullptr;
    }
    
    return ptr;
}

void STL::LinearAllocator::free(void* object, const STL::SourceInfo& info)
{
}