#pragma once

#include "SceneGraph.h"
#include "Unit.h"
#include "id_types.h"

#include <vector>

namespace Proteus
{
    class World
    {
    public:
        static const unsigned INVALID_MAGIC = 0;
        
        world_id_t id;
        
    private:
        struct scenegraph_t
        {
            Unit unit;
            unit_id_t id;
            
            //TODO move these to a seperate list-in-list (because level 0 does not use them)
            unit_id_t target;
            node_id_t target_node;
        };
        
        struct index_t
        {
            unsigned magic;
            unsigned level;
            size_t sg_index;
        };
        
        std::vector<std::vector<scenegraph_t>> scenegraphs;
        std::vector<index_t> indices;
        
        std::vector<size_t> indices_freelist;
        
        unsigned magic; //TODO rename to generation?
        
        void repack(const index_t& hole);
        void move_node(index_t& index, const unsigned new_level);

    public:
        World(world_id_t id);
        
        unit_id_t create_sg();
        void destroy_sg(const unit_id_t id);
        Unit& get(const unit_id_t id);
        
        //data will be copied FROM target TO source
        void link_sg(const unit_id_t source, const unit_id_t target, const node_id_t target_node);
        void unlink_sg(const unit_id_t source);
        void update_sgs();
        bool valid(const unit_id_t id) const;
    };
};