#pragma once

namespace stl
{
    class file;
    
    class archive
    {
    public:
        virtual file* open(const char* path, int mode) = 0;
    };
};