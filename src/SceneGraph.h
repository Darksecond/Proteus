#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <vector>

namespace Proteus
{
    //TODO scaling
    class SceneGraph
    {
    public:
        typedef size_t id_t;
        static const id_t NO_PARENT = -1;
        
    private:
        std::vector<glm::vec3> local_position;
        std::vector<glm::quat> local_rotation;
        std::vector<glm::vec3> global_position;
        std::vector<glm::quat> global_rotation;
        std::vector<id_t> parent;
        id_t node_count;
        
        void update_node(const id_t node);
        glm::mat4 matrix(const id_t node);
        
    public:
        SceneGraph();
        
        id_t add_node(const glm::vec3 position, const glm::quat rotation, const id_t parent_node = NO_PARENT);
        void update_nodes();
        
        //setters,getters
    };
};