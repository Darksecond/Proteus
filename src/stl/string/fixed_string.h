#pragma once

#include "types.h"
#include <cassert>
#include <cstdio>

namespace stl
{
    template<size_t N>
    class fixed_string
    {
        char _string[N];
        size_t _length;
    public:
        inline fixed_string() : _length(0)
        {
            _string[0] = 0;
        }
        
        explicit fixed_string(const char* const str) : _length(strlen(str))
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
        
        inline void append_fmt(const char* format, ...)
        {
            va_list formatters;
            va_start(formatters, format);
            const int chars_written = vsnprintf(_string + _length, N - _length, format, formatters);
            if(chars_written < 0)
            {
                //TODO warning!
                _length = N-1;
                _string[_length] = 0; //append null byte
            }
            else
            {
                _length += chars_written;
            }
            va_end(formatters);
        }
    };
}