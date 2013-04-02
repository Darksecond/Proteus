#include "HeapArea.h"

#include <stdlib.h>

stl::HeapArea::HeapArea(size_t s) : _start(nullptr), _size(0)
{
    reserve(s);
}

stl::HeapArea::~HeapArea()
{
    release();
}

stl::HeapArea::HeapArea(stl::HeapArea&& other) : _start(other.start()), _size(other.size())
{
    other._start = nullptr;
    other._size = 0;
}

stl::HeapArea& stl::HeapArea::operator=(stl::HeapArea&& other)
{
    release();
    
    _start = other.start();
    _size = other.size();
    
    other._start = nullptr;
    other._size = 0;
    
    return *this;
}

void stl::HeapArea::reserve(size_t new_size)
{
    if(_size == 0)
    {
        _start = ::malloc(new_size);
        _size = new_size;
    }
}

void stl::HeapArea::release()
{
    if(_size != 0)
    {
        ::free(_start);
        _start = nullptr;
        _size = 0;
    }
}