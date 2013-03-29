#pragma once

#include <stdlib.h>

#include "memory_internals.h"

//EXAMPLES:
//STL::MallocAllocator someArena;
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
        class Allocator
        {
        public:
            virtual void* allocate(size_t size, size_t align, size_t offset, const SourceInfo& info) = 0;
            virtual void free(void* object, const SourceInfo& info) = 0;
        };
        
        class MallocAllocator : public Allocator
        {
        public:
            //address+offset should be aligned, NOT address itself
            virtual void* allocate(size_t size, size_t align, size_t offset, const SourceInfo& info)
            {
                return ::malloc(size);
            }
            
            virtual void free(void* object, const SourceInfo& info)
            {
                ::free(object);
            }
        };
    };
};