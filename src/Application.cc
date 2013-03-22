#include "Application.h"

using namespace Proteus;

Application::Application() : worlds(), indices(), indices_freelist()
{
}

world_id_t Application::create_world()
{
    const size_t world_index = worlds.size();
    
    size_t indice_index;
    if(indices_freelist.size() == 0)
    {
        indice_index = indices.size();
        indices.push_back({0});
    }
    else
    {
        indice_index = indices_freelist.back();
        indices_freelist.pop_back();
    }
    
    const world_id_t new_id{indice_index};
    
    indices[indice_index] = {world_index};
    worlds.emplace_back(new_id);
    
    return new_id;
}

void Application::destroy_world(const world_id_t world)
{
    index_t& index = indices[world.index];
    World& to_remove = get_world(world);
    
    if(index.index != worlds.size()-1)
    {
        to_remove = std::move(worlds.back());
    }
    
    worlds.pop_back();
    indices[to_remove.id.index].index = index.index;
    
    indices_freelist.push_back(world.index);
}

World& Application::get_world(const world_id_t world)
{
    return worlds[indices[world.index].index];
}

World& Application::get_world(const unit_id_t unit)
{
    return worlds[indices[unit.world_id.index].index];
}

Unit& Application::get_unit(const unit_id_t unit)
{
    return worlds[indices[unit.world_id.index].index].get(unit);
}