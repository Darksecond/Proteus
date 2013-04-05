#include "log.h"
#include "types.h"


static stl::logger* loggers[8] = {nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr};

void stl::log::set_logger(logger* l, int i)
{
    loggers[i] = l;
}

void stl::log::log(stl::source_info& source_info, int level, const char* channel, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    for(logger* l: loggers)
    {
        if(l)
            l->log(source_info, level, channel, format, list);
    }
    
    va_end(list);
}