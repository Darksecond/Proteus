#include "World.h"

#include <stdexcept>

using namespace Proteus;

World::World(world_id_t id) : id(id), scenegraphs(), indices(), indices_freelist(), magic(1)
{
    scenegraphs.emplace_back(); //build level 0
}

unit_id_t World::create_sg()
{    
    const unsigned chosen_magic = magic++;
    const size_t scenegraphs_index = scenegraphs[0].size();
    static const unsigned level = 0;
    
    if(indices_freelist.size() == 0)
    {
        //build new
        const size_t indice_index = indices.size();
        
        const unit_id_t new_id{chosen_magic, indice_index, id};
        
        indices.push_back({chosen_magic, level, scenegraphs_index});
        scenegraphs[level].push_back({SceneGraph(), new_id});
        
        return new_id;
    }
    else
    {
        //reuse
        const size_t indice_index = indices_freelist.back();
        indices_freelist.pop_back();
        
        const unit_id_t new_id{chosen_magic, indice_index, id};
        
        indices[indice_index] = {chosen_magic, level, scenegraphs_index};
        scenegraphs[level].push_back({SceneGraph(), new_id});
        
        return new_id;
    }
}

void World::destroy_sg(const unit_id_t id)
{
    index_t& index = indices[id.index];
    
    if(index.magic != id.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
        
    repack(index);
    
    //mark the original index as free (and mark invalid)
    index.magic = INVALID_MAGIC;
    indices_freelist.push_back(id.index);
}

Unit& World::get(const unit_id_t id)
{
    const index_t& index = indices[id.index];
    
    if(index.magic != id.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
    
    return scenegraphs[index.level][index.sg_index].unit;
}

void World::update_sgs()
{
    for(auto& sg : scenegraphs[0])
    {
        sg.unit.scenegraph.update_nodes();
    }
    
    for(int i = 1; i < scenegraphs.size(); ++i)
    {        
        for(auto& sg : scenegraphs[i])
        {
            SceneGraph& target = get(sg.target).scenegraph;
            SceneGraph& source = sg.unit.scenegraph;
            
            //source.root() might throw an exception, i let that pass on up as it's a failure anyways
            source.set_local_position(source.root(), target.get_global_position(sg.target_node));
            source.set_local_rotation(source.root(), target.get_global_rotation(sg.target_node));
            
            sg.unit.scenegraph.update_nodes();
        }
    }
}

void World::link_sg(const unit_id_t source, const unit_id_t target, const node_id_t target_node)
{
    //TODO
    //make sure source has a root and target node has the actual node targetted
    index_t& source_index = indices[source.index];
    index_t& target_index = indices[target.index];
    
    if(source_index.magic != source.magic)
        throw std::runtime_error("Source magic does not match"); //TODO use 'real' exception
    if(target_index.magic != target.magic)
        throw std::runtime_error("Target magic does not match"); //TODO use 'real' exception
    if(source_index.level != 0)
        throw std::runtime_error("SG it already linked");
    scenegraphs[source_index.level][source_index.sg_index].unit.scenegraph.root(); //this will cause an exception is there is no root
    
    move_node(source_index, target_index.level + 1);
    
    //set target on source
    scenegraphs[source_index.level][source_index.sg_index].target = target;
    scenegraphs[source_index.level][source_index.sg_index].target_node = target_node;
}

void World::unlink_sg(const unit_id_t source)
{
    //get index
    index_t& index = indices[source.index];
    
    if(index.magic != source.magic)
        throw std::runtime_error("Magic does not match"); //TODO use 'real' exception
    
    if(index.level == 0)
        throw std::runtime_error("SG it not linked");
    
    move_node(index, 0);
}

void World::repack(const index_t& hole)
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

void World::move_node(index_t& index, const unsigned new_level)
{
    scenegraph_t& object = scenegraphs[index.level][index.sg_index];
    
    //create level if it does not exist yet
    if(new_level+1 > scenegraphs.size())
    {
        scenegraphs.emplace_back();
    }
    
    //move object to end of new_level
    size_t new_sg_index = scenegraphs[new_level].size();
    scenegraphs[new_level].push_back(std::move(object));
    
    repack(index);
    
    //repoint index
    index.level = new_level;
    index.sg_index = new_sg_index;
}