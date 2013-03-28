#pragma once

#include <stdint.h>

namespace Proteus
{
    namespace STL
    {
        template<class T>
        struct TypeAndCount
        {
        };
        
        template<class T, size_t N>
        struct TypeAndCount<T[N]>
        {
            typedef T Type;
            static const size_t Count = N;
        };
        
        template<bool I>
        struct BoolToType
        {
        };
    };
};