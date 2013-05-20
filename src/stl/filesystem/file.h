#pragma once

#include "stl/types.h"

namespace stl
{
    class file
    {
    public:
        virtual ~file() {}
        
        /**
         * Close the file so it can be safely deleted.
         */
        virtual void close() = 0;
        
        //read, errors, buffers, buffer size?
        /**
         * Read into buffer for a maximum of buf_size bytes.
         * Returns the amount of bytes read.
         */
        virtual size_t read(void* buffer, size_t buf_size) = 0;
        
        //virtual size_t write(const void* buffer, size_t buf_size) = 0;
        //write
        
        //async_read
        //async_write
        
        //streaming stuff?
        
        virtual void skip(size_t amount) = 0;
        virtual bool eof() = 0;
        virtual size_t total_size() = 0; //or get_remaining_bytes
    };
};