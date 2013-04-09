#pragma once

#include "stl/types.h"

namespace stl
{
    class archive;
    
    class file
    {
    public:
        archive* archive; //move this to private with friend or getters/setters?
        
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