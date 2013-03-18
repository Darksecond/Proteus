#pragma once

#include "SceneGraph.h"

#include <vector>

namespace Proteus
{
    //TODO implementation
    class SceneGraphSystem
    {
    public:
        typedef struct
        {
            //TODO
        } id_t;
        
    private:

    public:        
        id_t create_sg();
        void destroy_sg(const id_t sg);
        SceneGraph& get(const id_t sg);
        void link_sg(id_t source, id_t target, SceneGraph::id_t target_node);
        void update_sgs();
    };
};