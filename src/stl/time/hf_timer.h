#pragma once

#include "stl/types.h"
#include "stl/platform.h"

namespace stl
{
    class hf_timer
    {
    public:
        void start();
    
        double get_nanoseconds() const;
        double get_seconds() const;
        double get_milliseconds() const;
        
    private:
#ifdef P_PLATFORM_APPLE
        uint64_t _start;
#endif
    };
};