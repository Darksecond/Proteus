#pragma once

#include "stl/types.h"
#include "stl/string/string_hash.h"
#include "stl/filesystem/file.h"
#include "stl/memory.h"

namespace graphics
{
    class mesh_library
    {
    public:
        mesh_library(stl::arena* temporary, stl::arena* permanent);
        void on_load(uint32_t fourCC, stl::string_hash name, stl::file* file);
        //TODO add 'on_unload' which frees the vertex_buffer
        uint32_t get_chunk_4CC();
    private:
        stl::arena* _permanent_arena;
        stl::arena* _temporary_arena;
    };
};