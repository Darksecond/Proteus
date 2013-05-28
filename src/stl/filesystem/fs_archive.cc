#include "fs_archive.h"

#include "stl/memory/arena.h"
#include "stl/memory/new_delete.h"
#include "stl/string/fixed_string.h"
#include "fs_file.h"

#include <sys/stat.h>
#include <cassert>

stl::fs_archive::fs_archive(const char* directory, arena* arena) : _arena(arena), _directory(directory)
{
}

stl::file* stl::fs_archive::open(const char* path, int mode)
{
    fixed_string<512> full_path(_directory);
    full_path.append("/");
    full_path.append(path);
    
    struct stat buffer;
    bool exists = stat(full_path.c_str(), &buffer) == 0;
    if(exists)
        return P_NEW(*_arena, fs_file, full_path.c_str(), mode, this);
    else
        return nullptr;
}

void stl::fs_archive::close(file* file)
{
    assert(file);
    
    P_DELETE(*_arena, file);
}
