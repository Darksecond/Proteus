#pragma once

#include "stl/types.h"
#include "stl/string/string_hash.h"

#include "resource_id.h"

namespace stl
{
    class file;
};

class library
{
public:
    //TODO replace resource_type and resource_name with resource_id struct, or something
    virtual void load(resource_id id, stl::file* file) = 0;
    virtual void unload(resource_id id) = 0;
    virtual void link(resource_id id) = 0;
};