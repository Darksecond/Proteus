#pragma once

#include <stddef.h>

namespace Proteus
{
    typedef struct
    {
        size_t index;
        /* unsigned magic; */
    } world_id_t;
    
    typedef struct
    {
        unsigned magic;
        size_t index;
        world_id_t world_id;
    } unit_id_t;
    
    typedef size_t node_id_t;
};