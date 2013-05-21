#include "fs_archive.h"

#include "stl/memory/arena.h"
#include "stl/memory/new_delete.h"
#include "fs_file.h"

#include <sys/stat.h>
#include <cassert>

stl::fs_archive::fs_archive(arena* arena) : _arena(arena)
{
}

stl::file* stl::fs_archive::open(const char* path, int mode)
{
    struct stat buffer;
    bool exists = stat(path, &buffer) == 0;
    if(exists)
        return P_NEW(*_arena, fs_file, path, mode, this);
    else
        return nullptr;
}

void stl::fs_archive::close(file* file)
{
    assert(file);
    
    P_DELETE(*_arena, file);
}
