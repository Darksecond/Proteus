#pragma once

#include "types.h"
#include "hash.h"

namespace stl
{
    class string_hash
    {
    public:
        typedef uint64_t Type;
        
        constexpr string_hash(const char* str) : hash(Hash::hash_fnv1a(str))
        {
        }
        
        constexpr inline operator Type() const
        {
            return hash;
        }
        
    private:
        const Type hash;
    };
};