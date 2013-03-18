#pragma once

#include "SceneGraph.h"

#include <vector>
#include <list>

namespace Proteus
{
    //TODO implementation
    class SceneGraphSystem
    {
    public:
        typedef struct
        {
            unsigned magic;
            size_t index;
        } id_t;
        
    private:
        struct scenegraph_t
        {
            SceneGraph scenegraph;
            id_t id;
            /* id_t target */
            /* SceneGraph::id_t target_node */
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
        
        unsigned magic;

    public:
        SceneGraphSystem();
        
        id_t create_sg();
        void destroy_sg(const id_t id);
        SceneGraph& get(const id_t id);
        void link_sg(const id_t source, const id_t target, const SceneGraph::id_t target_node);
        void unlink_sg(const id_t source);
        void update_sgs();
    };
};