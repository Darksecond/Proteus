#pragma once

namespace stl
{
    class file;
    
    class archive
    {
    public:
        file* open(const char* path, int mode);
        void close(file* file);
    };
};