#include "root.h"

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
