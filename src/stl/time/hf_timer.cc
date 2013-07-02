#include "hf_timer.h"

#include <mach/mach_time.h>

void stl::hf_timer::start()
{
    _start = mach_absolute_time();
}

double stl::hf_timer::get_nanoseconds() const
{
    uint64_t end = mach_absolute_time();
    
    uint64_t elapsed = end - _start;
    
    static double conversion = 0.0;
    if(conversion == 0.0)
    {
        mach_timebase_info_data_t timebase_info;
        mach_timebase_info(&timebase_info);
        conversion = (double)timebase_info.numer / (double)timebase_info.denom;
    }
    
    return conversion * (double)elapsed;
}

double stl::hf_timer::get_seconds() const
{
    return get_nanoseconds() * 1e-9;
}

double stl::hf_timer::get_milliseconds() const
{
    return get_nanoseconds() * 1e-6;
}
