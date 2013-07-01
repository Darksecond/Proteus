#pragma once

#include <pthread.h>

namespace stl
{
    class mutex
    {
    public:
        mutex();
        ~mutex();
        
        /**
         * Lock the mutex, or wait until it can be locked
         */
        void lock();
        
        /**
         * Returns true when the lock was successfull
         */
        bool try_lock();
        
        /**
         Unlock the mutex
         */
        void unlock();
    private:
        pthread_mutex_t _mutex;
    };
};