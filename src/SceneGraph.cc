#include "SceneGraph.h"

using namespace Proteus;

#include <GLM/gtc/matrix_transform.hpp>
#include <stdexcept>

SceneGraph::SceneGraph() : local_position(0), local_rotation(0), global_position(0), global_rotation(0), parent(0), node_count(0)
{
}


SceneGraph::id_t SceneGraph::add_node(const glm::vec3 position, const glm::quat rotation, const id_t parent_node)
{
    if(parent_node > node_count && parent_node != NO_PARENT)
        throw std::runtime_error("Cannot set parent to a future node");

    local_position.push_back(position);
    local_rotation.push_back(rotation);
    global_position.push_back(position);
    global_rotation.push_back(rotation);
    parent.push_back(parent_node);
    
    update_node(node_count);
    
    return node_count++;
}

void SceneGraph::update_nodes()
{
    //TODO make parallel
    for(SceneGraph::id_t i = 0; i < node_count; ++i)
    {
        update_node(i);
    }
}

void SceneGraph::update_node(const id_t node)
{
    const id_t parent_node = parent[node];
    if(parent_node == NO_PARENT)
    {
        global_rotation[node] = local_rotation[node];
        global_position[node] = local_position[node];
    }
    else
    {
        global_rotation[node] = global_rotation[parent_node] * local_rotation[node];
        global_position[node] = global_position[parent_node] + global_rotation[node] * local_position[node];
    }
}

glm::mat4 SceneGraph::matrix(const id_t node) const
{
    glm::mat4 matrix = glm::translate(glm::mat4(), -global_position[node]);
    matrix = matrix * glm::mat4_cast(global_rotation[node]);
    
    return matrix;
}
