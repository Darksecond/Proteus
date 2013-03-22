#pragma once

#include "id_types.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <vector>
#include <stdexcept>

namespace Proteus
{
    //TODO scaling
    class SceneGraph
    {
    public:
        static const node_id_t NO_PARENT = -1;
        
    private:
        std::vector<glm::vec3> local_position;
        std::vector<glm::quat> local_rotation;
        std::vector<glm::vec3> global_position;
        std::vector<glm::quat> global_rotation;
        std::vector<node_id_t> parent;
        node_id_t node_count;
        
        void update_node(const node_id_t node);
        glm::mat4 matrix(const node_id_t node) const;
        
    public:
        SceneGraph();
        
        node_id_t add_node(const glm::vec3 position, const glm::quat rotation, const node_id_t parent_node = NO_PARENT);
        void update_nodes();
        
        //setters,getters
        inline void set_local_position(const node_id_t id, const glm::vec3 new_pos);
        inline void set_local_rotation(const node_id_t id, const glm::quat new_rot);
        
        inline glm::vec3 get_global_position(const node_id_t id) const;
        inline glm::quat get_global_rotation(const node_id_t id) const;
        
        inline node_id_t root() const;
    };
    
    // --- INLINED METHODS ---
    
    void SceneGraph::set_local_position(const node_id_t id, const glm::vec3 new_pos)
    {
        local_position[id] = new_pos;
    }
    
    void SceneGraph::set_local_rotation(const node_id_t id, const glm::quat new_rot)
    {
        local_rotation[id] = new_rot;
    }
    
    glm::vec3 SceneGraph::get_global_position(const node_id_t id) const
    {
        return global_position[id];
    }

    glm::quat SceneGraph::get_global_rotation(const node_id_t id) const
    {
        return global_rotation[id];
    }

    node_id_t SceneGraph::root() const
    {
        if(node_count == 0)
            throw std::runtime_error("No root node");
        
        return 0;
    }
};