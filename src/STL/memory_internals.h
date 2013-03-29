#pragma once

#include <type_traits>

#include "types.h"
#include "log.h"

#define P_NEW(arena, type, ...) (new ((arena).allocate(sizeof(type), alignof(type), 0, P_SOURCEINFO)) type(__VA_ARGS__))

#define P_DELETE(arena, object) Proteus::STL::MemoryInternals::Delete(arena, object, P_SOURCEINFO)

#define P_NEW_ARRAY(arena, type) Proteus::STL::MemoryInternals::NewArray<Proteus::STL::TypeAndCount<type>::Type>(arena, Proteus::STL::TypeAndCount<type>::Count, P_SOURCEINFO, Proteus::STL::BoolToType<std::is_pod<Proteus::STL::TypeAndCount<type>::Type>::value>())

#define P_DELETE_ARRAY(arena, ptr) Proteus::STL::MemoryInternals::DeleteArray(arena, ptr, P_SOURCEINFO);

namespace Proteus
{
    namespace STL
    {
        namespace MemoryInternals
        {
            typedef BoolToType<false> NonPODType;
            typedef BoolToType<true> PODType;
            
            template<class A, typename T>
            void Delete(A& alloc, T* object, const SourceInfo& info)
            {
                if(object)
                {
                    object->~T();
                    alloc.free(object, info);
                }
            }
            
            template<typename T, class A>
            T* NewArray(A& alloc, size_t count, const SourceInfo& info, PODType)
            {
                return static_cast<T*>(alloc.allocate(sizeof(T) * count, alignof(T), 0, info));
            }
            
            template<typename T, class A>
            T* NewArray(A& alloc, size_t count, const SourceInfo& info, NonPODType)
            {
                union
                {
                    void* as_void;
                    size_t* as_size_t;
                    T* as_T;
                };
                
                as_void = alloc.allocate( sizeof(T) * count + sizeof(size_t), alignof(T), sizeof(size_t) );
                
                *as_size_t++ = count;

                const T* const end = as_T + count;
                
                while(as_T < end)
                {
                    new (as_T++) T;
                }
                
                return (as_T - count);
            }
            
            template<typename T, class A>
            void DeleteArray(A& alloc, T* ptr, const SourceInfo& info, PODType)
            {
                alloc.free(ptr, info);
            }
            
            template<typename T, class A>
            void DeleteArray(A& alloc, T* ptr, const SourceInfo& info, NonPODType)
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
                
                alloc.free(as_size_t-1, info);
            }
            
            template <typename T, class A>
            void DeleteArray(A& arena, T* ptr, const SourceInfo& info)
            {
                if(ptr)
                    DeleteArray(arena, ptr, info, BoolToType<std::is_pod<T>::value>());
            }
        }
    };
};