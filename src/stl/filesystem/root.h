#pragma once

#include "stl/types.h"
#include "stl/containers/dynamic_array.h"

namespace stl
{
    class archive;
    class arena;
    
    class root
    {
        dynamic_array<archive*> _mounts;
    public:
        root(arena* arena, int capacity);
        
        void mount(archive*);
        void unmount(archive*);
        
        //File* open(path, mode);
        //void close(path);
    };
};