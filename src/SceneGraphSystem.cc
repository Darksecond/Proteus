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
    for(auto& sg : scenegraphs[0])
    {
        sg.scenegraph.update_nodes();
    }
    
    for(int i = 1; i < scenegraphs.size(); ++i)
    {        
        for(auto& sg : scenegraphs[i])
        {
            SceneGraph& target = get(sg.target);
            SceneGraph& source = sg.scenegraph;
            
            //source.root() might throw an exception, i let that pass as it's a failure anyways
            source.set_local_position(source.root(), target.get_global_position(sg.target_node));
            source.set_local_rotation(source.root(), target.get_global_rotation(sg.target_node));
            
            sg.scenegraph.update_nodes();
        }
    }
}

void SceneGraphSystem::link_sg(const id_t source, const id_t target, const SceneGraph::id_t target_node)
{
    //TODO
    //make sure source has a root and target node has the actual node targetted
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