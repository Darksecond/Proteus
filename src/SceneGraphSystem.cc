#include "SceneGraphSystem.h"

#include <stdexcept>

using namespace Proteus;

SceneGraphSystem::SceneGraphSystem() : scenegraphs(), indices(), indices_freelist(), magic(1)
{
    scenegraphs.emplace_back(); //build level 0
}

SceneGraphSystem::id_t SceneGraphSystem::create_sg()
{    
    const unsigned chosen_magic = magic++;
    const size_t scenegraphs_index = scenegraphs[0].size();
    static const unsigned level = 0;
    
    if(indices_freelist.size() == 0)
    {
        //build new
        const size_t indice_index = indices.size();
        
        const id_t new_id{chosen_magic, indice_index};
        
        indices.push_back({chosen_magic, level, scenegraphs_index});
        scenegraphs[level].push_back({SceneGraph(), new_id});
        
        return new_id;
    }
    else
    {
        //reuse
        const size_t indice_index = indices_freelist.back();
        indices_freelist.pop_back();
        
        const id_t new_id{chosen_magic, indice_index};
        
        indices[indice_index] = {chosen_magic, level, scenegraphs_index};
        scenegraphs[level].push_back({SceneGraph(), new_id});
        
        return new_id;
    }
}

void SceneGraphSystem::destroy_sg(const id_t id)
{
    index_t& index = indices[id.index];
    
    if(index.magic != id.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
    
    scenegraph_t& object = scenegraphs[index.level][index.sg_index];
    
    //move last object
    object = scenegraphs[index.level].back();
    scenegraphs[index.level].pop_back();
    
    //point index to new location, level and magic stay the same
    indices[object.id.index].sg_index = index.sg_index;
    
    //mark the original index as free (and mark invalid)
    index.magic = 0;
    indices_freelist.push_back(id.index);
}

SceneGraph& SceneGraphSystem::get(const id_t id)
{
    index_t& index = indices[id.index];
    
    if(index.magic != id.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
    
    return scenegraphs[index.level][index.sg_index].scenegraph;
}

void SceneGraphSystem::update_sgs()
{
    for(auto& level : scenegraphs)
    {
        for(auto& sg : level)
        {
            //TODO load data from previous level (if this node is linked)
            sg.scenegraph.update_nodes();
        }
    }
}