#include "memory.h"

#include <stdlib.h>

using namespace Proteus;

STL::HeapArea::HeapArea(size_t s) : _start(nullptr), _size(0)
{
    reserve(s);
}

STL::HeapArea::~HeapArea()
{
    release();
}

STL::HeapArea::HeapArea(STL::HeapArea&& other) : _start(other.start()), _size(other.size())
{
    other._start = nullptr;
    other._size = 0;
}

STL::HeapArea& STL::HeapArea::operator=(STL::HeapArea&& other)
{
    release();
    
    _start = other.start();
    _size = other.size();
    
    other._start = nullptr;
    other._size = 0;
    
    return *this;
}

void STL::HeapArea::reserve(size_t new_size)
{
    if(_size == 0)
    {
        _start = ::malloc(new_size);
        _size = new_size;
    }
}

void STL::HeapArea::release()
{
    if(_size != 0)
    {
        ::free(_start);
        _start = nullptr;
        _size = 0;
    }
}

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
        //TODO make this a config option, maybe template
        //TODO print very much visible warning
        return fallbackAllocator().allocate(size, alignment, alignment_offset, info);
        //return nullptr;
    }
    
    return ptr;
}

void STL::LinearAllocator::free(void* object, const STL::SourceInfo& info)
{
    if(object < _start || object > _end)
    {
        //TODO make this a config option, maybe template
        fallbackAllocator().free(object, info);
    }
}

//address+offset should be aligned, NOT address itself
void* STL::FallbackAllocator::allocate(size_t size, size_t align, size_t offset, const STL::SourceInfo& info)
{
    return ::malloc(size);
}

void STL::FallbackAllocator::free(void* object, const STL::SourceInfo& info)
{
    ::free(object);
}


STL::FallbackAllocator _fallback_allocator;
STL::FallbackAllocator& STL::fallbackAllocator()
{
    return _fallback_allocator;
}