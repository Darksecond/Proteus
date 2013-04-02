#pragma once

#include <type_traits>

#include "types.h"
#include "log.h"

#define P_NEW(arena, type, ...) (new ((arena).allocate(sizeof(type), alignof(type), 0, P_SOURCEINFO)) type(__VA_ARGS__))

#define P_DELETE(arena, object) stl::memory_internals::delete_mem(arena, object, P_SOURCEINFO)

#define P_NEW_ARRAY(arena, type) stl::memory_internals::new_array_mem<stl::type_and_count<type>::Type>(arena, stl::type_and_count<type>::Count, P_SOURCEINFO, stl::bool_to_type<std::is_pod<stl::type_and_count<type>::Type>::value>())

#define P_DELETE_ARRAY(arena, ptr) stl::memory_internals::delete_array_pointer(arena, ptr, P_SOURCEINFO);

namespace stl
{
    namespace memory_internals
    {
        //TODO move this out to another file
        inline void* align_forward(void* p, size_t align)
        {
            uintptr_t pi = uintptr_t(p);
            const size_t mod = pi % align;
            if (mod)
                pi += (align - mod);
            return (void*)pi;
        }
        
        typedef bool_to_type<false> NonPODType;
        typedef bool_to_type<true> PODType;
        
        template<class A, typename T>
        void delete_mem(A& alloc, T* object, const source_info& info)
        {
            if(object)
            {
                object->~T();
                alloc.free(object, info);
            }
        }
        
        template<typename T, class A>
        T* new_array_mem(A& alloc, size_t count, const source_info& info, PODType)
        {
            return static_cast<T*>(alloc.allocate(sizeof(T) * count, alignof(T), 0, info));
        }
        
        template<typename T, class A>
        T* new_array_mem(A& alloc, size_t count, const source_info& info, NonPODType)
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
        void delete_array_mem(A& alloc, T* ptr, const source_info& info, PODType)
        {
            alloc.free(ptr, info);
        }
        
        template<typename T, class A>
        void delete_array_mem(A& alloc, T* ptr, const source_info& info, NonPODType)
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
        void delete_array_mem(A& arena, T* ptr, const source_info& info)
        {
            if(ptr)
                delete_array_mem(arena, ptr, info, bool_to_type<std::is_pod<T>::value>());
        }
    }
};