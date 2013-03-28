#pragma once

#include <type_traits>
#include <stdlib.h> //TEMP (for malloc, free)

#include "types.h"
#include "log.h"

//also pass __FILE__ and __LINE__ as parameters
#define P_NEW(arena, type, ...) (new ((arena).allocate(sizeof(type), alignof(type), 0, P_SOURCEINFO)) type(__VA_ARGS__))

#define P_DELETE(arena, object) Proteus::STL::Delete(arena, object, P_SOURCEINFO)

//also pass __FILE__ and __LINE__ as parameters
#define P_NEW_ARRAY(arena, type) Proteus::STL::NewArray<Proteus::STL::TypeAndCount<type>::Type>(arena, Proteus::STL::TypeAndCount<type>::Count, P_SOURCEINFO, Proteus::STL::BoolToType<std::is_pod<Proteus::STL::TypeAndCount<type>::Type>::value>())

#define P_DELETE_ARRAY(arena, ptr) Proteus::STL::DeleteArray(arena, ptr, P_SOURCEINFO);

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
        typedef BoolToType<false> NonPODType;
        typedef BoolToType<true> PODType;
        
        class MallocArena
        {
        public:
            //address+offset should be aligned, NOT address itself
            void* allocate(size_t size, size_t align, size_t offset, const SourceInfo& info)
            {
                return ::malloc(size);
            }
            
            void free(void* object, const SourceInfo& info)
            {
                ::free(object);
            }
        };
        
        template<class A, typename T>
        void Delete(A& arena, T* object, const SourceInfo& info)
        {
            if(object)
            {
                object->~T();
                arena.free(object, info);
            }
        }
        
        template<typename T, class A>
        T* NewArray(A& arena, size_t count, const SourceInfo& info, PODType)
        {
            return static_cast<T*>(arena.allocate(sizeof(T) * count, alignof(T), 0, info));
        }
        
        template<typename T, class A>
        T* NewArray(A& arena, size_t count, const SourceInfo& info, NonPODType)
        {
            union
            {
                void* as_void;
                size_t* as_size_t;
                T* as_T;
            };
            
            as_void = arena.allocate( sizeof(T) * count + sizeof(size_t), alignof(T), sizeof(size_t) );
            
            *as_size_t++ = count;

            const T* const end = as_T + count;
            
            while(as_T < end)
            {
                new (as_T++) T;
            }
            
            return (as_T - count);
        }
        
        template <typename T, class A>
        void DeleteArray(A& arena, T* ptr, const SourceInfo& info)
        {
            if(ptr)
                DeleteArray(arena, ptr, info, BoolToType<std::is_pod<T>::value>());
        }
        
        template<typename T, class A>
        void DeleteArray(A& arena, T* ptr, const SourceInfo& info, PODType)
        {
            arena.free(ptr, info);
        }
        
        template<typename T, class A>
        void DeleteArray(A& arena, T* ptr, const SourceInfo& info, NonPODType)
        {
            union
            {
                size_t* as_size_t;
                T* as_T;
            };
            
            as_T = ptr;
            
            const size_t count = as_size_t[-1];
            
            for(size_t i = count; i > 0; --i)
                as_T[i-1].~T();
            
            arena.free(as_size_t-1, info);
        }
    };
};