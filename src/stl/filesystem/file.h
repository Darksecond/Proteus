#pragma once

#include "stl/types.h"

namespace stl
{
    class archive;
    
    class file
    {
        archive* _owner;
    public:
        file(archive* owner) : _owner(owner)
        {
        }
        
        virtual ~file()
        {
        }
        
        /**
         * Read into buffer for a maximum of buf_size bytes.
         * Returns the amount of bytes read.
         */
        virtual size_t read(void* buffer, size_t buf_size) = 0;
        
        template <typename T>
        inline size_t read(T& object)
        {
            return read(&object, sizeof(T));
        }
        
        //virtual size_t write(const void* buffer, size_t buf_size) = 0;
        //write
        
        //async_read
        //async_write
        
        //streaming stuff?
        
        virtual void skip(size_t amount) = 0;
        virtual bool eof() const = 0; //or get_remaining_bytes
        virtual size_t total_size() = 0;
        
        archive* owner() const
        {
            return _owner;
        }
    };
};