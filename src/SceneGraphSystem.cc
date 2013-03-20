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
        
    repack(index);
    
    //mark the original index as free (and mark invalid)
    index.magic = INVALID_MAGIC;
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

void SceneGraphSystem::link_sg(const id_t source, const id_t target, const SceneGraph::id_t target_node)
{
    //TODO
}

void SceneGraphSystem::unlink_sg(const id_t source)
{
    //get index
    index_t& index = indices[source.index];
    
    if(index.magic != source.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
    
    if(index.level == 0)
        throw std::runtime_error("SG it not linked");
    
    scenegraph_t& object = scenegraphs[index.level][index.sg_index];

    //move object to end of level 0
    size_t new_sg_index = scenegraphs[0].size();
    scenegraphs[0].push_back(std::move(object));
    
    repack(index);
    
    //repoint index
    index.level = 0;
    index.sg_index = new_sg_index;
}

void SceneGraphSystem::repack(const index_t& hole)
{
    scenegraph_t& hole_object = scenegraphs[hole.level][hole.sg_index];
    
    //repack index.level, move last object
    if(scenegraphs[hole.level].size() != hole.sg_index+1)
    {
        hole_object = std::move(scenegraphs[hole.level].back());
    }
    
    scenegraphs[hole.level].pop_back();
    
    //point index of repacked object to new location, level and magic stay the same
    indices[hole_object.id.index].sg_index = hole.sg_index;
}