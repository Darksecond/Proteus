#pragma once

#include "stl/types.h"
#include "stl/containers/dynamic_array.h"

namespace stl
{
    class archive;
    class arena;
    class file;
    
    class root
    {
        dynamic_array<archive*> _mounts;
    public:
        root(arena* arena, int capacity);
        
        void mount(archive*);
        void unmount(archive*);
        
        /**
         * Open a file with path and mode.
         * Returns a nullptr if the file does not exist.
         */
        file* open(const char* path, int mode);
        
        /**
         * Close a previously opened with 'open'.
         * This also deletes the file.
         */
        void close(file* file);
    };
};