#include "root.h"

#include "archive.h"
#include "file.h"

stl::root::root(arena* arena, int capacity) : _mounts(arena, capacity)
{
}

void stl::root::mount(archive* archive)
{
    _mounts.add(archive);
}

void stl::root::unmount(archive* archive)
{
    _mounts.erase(archive);
}

stl::file* stl::root::open(const char* path, int mode)
{
    //TODO
    //loop through archives
    file* retval = nullptr;
    for(archive* mount : _mounts)
    {
        retval = mount->open(path, mode);
        if(retval)
            break;
    }
    return retval;
}

void stl::root::close(file* file)
{
    //TODO
    file->archive->close(file);
}