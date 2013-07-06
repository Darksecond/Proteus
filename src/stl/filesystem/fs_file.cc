#include "fs_file.h"

#include "modes.h"

stl::fs_file::fs_file(const char* path, int mode, archive* owner) : stl::file(owner)
{
    std::ios_base::openmode f_mode = std::ios_base::binary;
    if(mode & fs_modes::in)
        f_mode = f_mode | std::ios_base::in;
    if(mode & fs_modes::out)
        f_mode = f_mode | std::ios_base::out;
    if(mode & fs_modes::append)
        f_mode = f_mode | std::ios_base::app;
    
    _stream = std::fstream(path, f_mode);
}

size_t stl::fs_file::read(void* buffer, size_t buf_size)
{
    _stream.read(static_cast<char*>(buffer), buf_size);
    return _stream.gcount();
}

void stl::fs_file::write(const void* buffer, size_t buf_size)
{
    _stream.write(static_cast<const char*>(buffer), buf_size);
}

void stl::fs_file::skip(size_t amount)
{
    _stream.seekg(amount, std::ios_base::cur);
}

void stl::fs_file::seek(size_t position)
{
    _stream.seekg(position, std::ios_base::beg);
}

bool stl::fs_file::eof() const
{
    return _stream.eof();
}

size_t stl::fs_file::total_size()
{
    std::streampos cur = _stream.tellg();
    _stream.seekg(0, std::ios::end);
    std::streampos size = _stream.tellg();
    _stream.seekg(cur);
    return size;
}