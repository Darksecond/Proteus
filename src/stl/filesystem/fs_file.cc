#include "fs_file.h"

#include "modes.h"

stl::fs_file::fs_file(const char* path, int mode, archive* owner) : stl::file(owner)
{
    //TODO: cannot set an ifstream to out mode!
    std::ios_base::openmode f_mode = std::ios_base::binary;
    if(mode & fs_modes::in)
        f_mode = f_mode | std::ios_base::in;
    if(mode & fs_modes::out)
        f_mode = f_mode | std::ios_base::out;
    if(mode & fs_modes::append)
        f_mode = f_mode | std::ios_base::app;
    
    _stream = std::ifstream(path, f_mode);
}

size_t stl::fs_file::read(void* buffer, size_t buf_size)
{
    char* char_buffer = reinterpret_cast<char*>(buffer);
    _stream.read(char_buffer, buf_size);
    return _stream.gcount();
}

void stl::fs_file::skip(size_t amount)
{
    _stream.seekg(amount, std::ios_base::cur);
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