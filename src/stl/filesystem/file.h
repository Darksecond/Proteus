#pragma once

#include "stl/types.h"

namespace stl
{
    class file
    {
    public:
        virtual void close() = 0;
        
        //read, errors, buffers, buffer size?
        //write
        
        //async_read
        //async_write
        
        //streaming stuff?
        
        //seek
        //skip
        
        //eof
        
        //total_size
    };
};