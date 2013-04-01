#pragma once

#include "types.h"
#include <cassert>

namespace STL
{
    template<size_t N>
    class FixedString
    {
        char _string[N];
        size_t _length;
    public:
        inline FixedString() : _length(0)
        {
            _string[0] = 0;
        }
        
        explicit FixedString(const char* const str) : _length(strlen(str))
        {
            assert(_length < N);
            memcpy(_string, str, _length+1); //copy null byte as well
        }
        
        void clear()
        {
            _length = 0;
            _string[0] = 0;
        }
        
        inline char& operator[](size_t i)
        {
            assert(i <= _length);
            return _string[i];
        }
        
        inline const char& operator[](size_t i) const
        {
            assert(i <= _length);
            return _string[i];
        }
        
        inline const char* c_str() const
        {
            return _string;
        }
        
        inline size_t length() const
        {
            return _length;
        }
        
        inline void append(const char* str, size_t count)
        {
            assert(_length + count < N);
            
            memcpy(_string + _length, str, count);
            _length += count;
            _string[_length] = 0;
        }
        
        inline void append(const char* str)
        {
            append(str, strlen(str));
        }
    };
}