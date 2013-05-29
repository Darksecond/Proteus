#pragma once

#include "stl/string/string_hash.h"

struct resource_id
{
    stl::string_hash name;
    stl::string_hash type;
};