#pragma once

#include "types.h"

namespace stl
{
    class HeapArea
    {
        void* _start;
        size_t _size;
    public:
        explicit HeapArea(size_t s);
        ~HeapArea();
        
        HeapArea(HeapArea& other) = delete;
        HeapArea& operator=(HeapArea& other) = delete;
        
        HeapArea(HeapArea&& other);
        HeapArea& operator=(HeapArea&& other);
        
        void reserve(size_t new_size);
        void release();
        
        inline void* start() { return _start; }
        inline void* end() { return (uint8_t*)_start + _size; }
        inline size_t size() { return _size; }
    };
};