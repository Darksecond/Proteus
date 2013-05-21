#pragma once

#include "stl/filesystem/archive.h"

namespace stl
{
    class arena;
    
    class fs_archive : public archive
    {
        arena* _arena;
    public:
        fs_archive(arena* arena);
        
        virtual file* open(const char* path, int mode) override;
        virtual void close(file* file) override;
    };
};