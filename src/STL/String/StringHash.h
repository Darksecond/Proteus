#pragma once

#include "types.h"
#include "hash.h"

namespace stl
{
    class StringHash
    {
    public:
        typedef uint64_t Type;
        
        constexpr StringHash(const char* str) : hash(Hash::hash_fnv1a(str))
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