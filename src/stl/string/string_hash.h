#pragma once

#include "types.h"
#include "hash.h"

namespace stl
{
    class string_hash
    {
    public:
        typedef uint64_t Type;
        
        constexpr string_hash(const char* str) : hash(hash::hash_fnv1a(str))
#ifdef DEBUG
        , original_string(str)
#endif
        {
        }
        
        constexpr inline operator Type() const
        {
            return hash;
        }
        
#ifdef DEBUG
        constexpr inline const char* string()
        {
            return original_string;
        }
#endif
        
    private:
        const Type hash;
#if DEBUG
        const char* const original_string;
#endif
    };
};