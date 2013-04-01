#pragma once

#include "types.h"
#include <cassert>

namespace STL
{
    template<size_t N>
    class FixedString
    {
        char string[N];
        size_t _length;
    public:
        inline FixedString() : _length(0)
        {
            string[0] = 0;
        }
        
        explicit FixedString(const char* const str) : _length(strlen(str))
        {
            assert(_length < N);
            memcpy(string, str, _length+1); //copy null byte as well
        }
        
        void clear()
        {
            _length = 0;
            string[0] = 0;
        }
        
        inline char& operator[](size_t i)
        {
            assert(i <= _length);
            return string[i];
        }
        
        inline const char& operator[](size_t i) const
        {
            assert(i <= _length);
            return string[i];
        }
        
        inline const char* c_str() const
        {
            return string;
        }
        
        inline size_t length() const
        {
            return _length;
        }
    };
}