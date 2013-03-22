#pragma once

#include "World.h"
#include "Unit.h"
#include "id_types.h"

#include <vector>

namespace Proteus
{
    class Application
    {
        struct index_t
        {
            /* unsigned magic; */
            size_t index;
        };
        
        std::vector<World> worlds;
        
        std::vector<index_t> indices;
        std::vector<size_t> indices_freelist;
    public:
        Application();
        
        world_id_t create_world();
        void destroy_world(const world_id_t world);
        World& get_world(const world_id_t world);
        World& get_world(const unit_id_t unit);
        
        Unit& get_unit(const unit_id_t unit);
    };
};