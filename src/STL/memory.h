#pragma once

#include "memory_internals.h"

//EXAMPLES:
//STL::FalbackAllocator& someArena = fallbackAllocator();
//int* a = P_NEW(someArena, int, 3);
//P_DELETE(someArena, a);
//int* b = P_NEW_ARRAY(someArena, int[3]);
//P_DELETE_ARRAY(someArena, b);
/*
 struct alignas(128) bigalign
 {
 uint64_t i[2];
 };
 */

namespace Proteus
{
    namespace STL
    {
        //TODO add 'arena' class-range after all
        //TODO allocators with constructor with start and end address
        //TODO write more allocators (pool, linear, stack)
        //TODO read molecular musings blog for more information!
        //TODO write a macro to re-size a size to include the P_NEW_ARRAY overhead
        //TODO remove fallbackAllocator() method
        
        class HeapArea
        {
            void* _start;
            size_t _size;
        public:
            HeapArea(size_t s);
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
        
        class LinearAllocator
        {
            uint8_t* _start;
            uint8_t* _end;
            uint8_t* _current;
        public:
            LinearAllocator(const void* start, const void* end);
            
            //address+offset should be aligned, NOT address itself
            void* allocate(const size_t size, const size_t align, const size_t alignment_offset, const STL::SourceInfo& info);
            void free(void* object, const STL::SourceInfo& info);
            inline void reset() { _current = _start; }
        };
        
        class FallbackAllocator
        {
        public:
            //address+offset should be aligned, NOT address itself
            void* allocate(size_t size, size_t align, size_t offset, const STL::SourceInfo& info);
            void free(void* object, const STL::SourceInfo& info);
        };
        
        FallbackAllocator& fallbackAllocator();
    };
};