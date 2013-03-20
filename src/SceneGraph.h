#pragma once

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
        glm::mat4 matrix(const id_t node) const;
        
    public:
        SceneGraph();
        
        id_t add_node(const glm::vec3 position, const glm::quat rotation, const id_t parent_node = NO_PARENT);
        void update_nodes();
        
        //setters,getters
        inline void set_local_position(const id_t id, const glm::vec3 new_pos);
        inline void set_local_rotation(const id_t id, const glm::quat new_rot);
        
        inline glm::vec3 get_global_position(const id_t id) const;
        inline glm::quat get_global_rotation(const id_t id) const;
        
        inline id_t root() const;
    };
    
    // --- INLINED METHODS ---
    
    void SceneGraph::set_local_position(const id_t id, const glm::vec3 new_pos)
    {
        local_position[id] = new_pos;
    }
    
    void SceneGraph::set_local_rotation(const id_t id, const glm::quat new_rot)
    {
        local_rotation[id] = new_rot;
    }
    
    glm::vec3 SceneGraph::get_global_position(const id_t id) const
    {
        return global_position[id];
    }

    glm::quat SceneGraph::get_global_rotation(const id_t id) const
    {
        return global_rotation[id];
    }

    SceneGraph::id_t SceneGraph::root() const
    {
        if(node_count == 0)
            throw std::runtime_error("No root node");
        
        return 0;
    }
};