#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <vector>

namespace Proteus
{
    class SceneGraph
    {
    public:
        typedef size_t id_t;
        
    private:
        std::vector<glm::vec3> local_position;
        std::vector<glm::quat> local_rotation;
        std::vector<glm::vec3> global_position;
        std::vector<glm::quat> global_rotation;
        std::vector<id_t> parent;
        id_t node_count;
        
        void update_node(id_t node);
        
    public:
        SceneGraph();
        
        id_t add_node(glm::vec3 position, glm::quat rotation, id_t parent_node = -1);
        void update_nodes();
        
        //setters,getters
    };
};