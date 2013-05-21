#pragma once

#include "stl/filesystem/file.h"

#include <fstream>

namespace stl
{
    class fs_file : public file
    {
        std::ifstream _stream;
    public:
        fs_file(const char* path, int mode, archive* owner);
        
        virtual size_t read(void* buffer, size_t buf_size);
        virtual void skip(size_t amount);
        virtual bool eof() const;
        virtual size_t total_size();
    };
};