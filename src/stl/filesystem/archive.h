#pragma once

namespace stl
{
    class file;
    
    class archive
    {
    public:
        /**
         * Open a file with path and mode if it exists.
         * Returns nullptr if the file does not exist.
         * The caller gets the ownership of the file.
         */
        virtual file* open(const char* path, int mode) = 0;
    };
};