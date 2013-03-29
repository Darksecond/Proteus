#pragma once

#include "types.h"

namespace Proteus
{
    namespace STL
    {
        //code from: http://seanmiddleditch.com/journal/2011/05/compile-time-string-hashing-in-c0x/
        namespace StringHash
        {
            // FNV-1a constants
            static constexpr uint64_t basis = 14695981039346656037ULL;
            static constexpr uint64_t prime = 1099511628211ULL;
            
            // compile-time hash helper function
            constexpr uint64_t hash_one(char c, const char* remain, uint64_t value)
            {
                return c == 0 ? value : hash_one(remain[0], remain + 1, (value ^ c) * prime);
            }
            
            // compile-time hash
            constexpr uint64_t hash(const char* str)
            {
                return hash_one(str[0], str + 1, basis);
            }
            
            // run-time hash
            uint64_t hash_rt(const char* str)
            {
                unsigned long long hash = basis;
                while (*str != 0) {
                    hash ^= str[0];
                    hash *= prime;
                    ++str;
                }
                return hash;
            }
        };
    };
};