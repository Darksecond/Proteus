#pragma once

#include "stl/types.h"

template <size_t iN, size_t gN>
struct generic_handle
{
    uint32_t index : iN;
    uint32_t generation : gN;
};