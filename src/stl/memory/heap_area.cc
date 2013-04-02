#include "heap_area.h"

#include <stdlib.h>

stl::heap_area::heap_area(size_t s) : _start(nullptr), _size(0)
{
    reserve(s);
}

stl::heap_area::~heap_area()
{
    release();
}

stl::heap_area::heap_area(stl::heap_area&& other) : _start(other.start()), _size(other.size())
{
    other._start = nullptr;
    other._size = 0;
}

stl::heap_area& stl::heap_area::operator=(stl::heap_area&& other)
{
    release();
    
    _start = other.start();
    _size = other.size();
    
    other._start = nullptr;
    other._size = 0;
    
    return *this;
}

void stl::heap_area::reserve(size_t new_size)
{
    if(_size == 0)
    {
        _start = ::malloc(new_size);
        _size = new_size;
    }
}

void stl::heap_area::release()
{
    if(_size != 0)
    {
        ::free(_start);
        _start = nullptr;
        _size = 0;
    }
}