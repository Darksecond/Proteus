#include "HeapArea.h"

#include <stdlib.h>

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