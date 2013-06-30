#pragma once

#include <pthread.h>

namespace stl
{
    class thread
    {
        enum class state_t
        {
            READY,
            RUNNING,
            SHOULD_STOP,
            STOPPED,
        };
    public:
        typedef void (*function)(const thread&);
        
        thread();
        ~thread();
        
        void create(const char* name, function f);
        void destroy();
        
        void join();
        void stop();
        
        bool should_stop() const;
        bool is_stopped() const;
        
        void yield();
    private:
        static void* thread_main_function(void* thread);
        function _function;
        state_t _state;
        pthread_t _thread;
        const char* _name;
    };
};