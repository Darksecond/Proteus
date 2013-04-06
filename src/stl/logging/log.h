#pragma once

#include <cstdarg>

#define P_SOURCEINFO stl::source_info{__FILE__, __FUNCTION__, __LINE__}

#define P_LOG(level, channel, format, ...) stl::log::log(P_SOURCEINFO, level, channel, format, __VA_ARGS__)
#define P_LDEBUG(channel, format, ...) stl::log::log(P_SOURCEINFO, 4, channel, format, __VA_ARGS__)
#define P_LINFO(channel, format, ...) stl::log::log(P_SOURCEINFO, 3, channel, format, __VA_ARGS__)
#define P_LWARNING(channel, format, ...) stl::log::log(P_SOURCEINFO, 2, channel, format, __VA_ARGS__)
#define P_LERROR(channel, format, ...) stl::log::log(P_SOURCEINFO, 1, channel, format, __VA_ARGS__)
#define P_LFATAL(channel, format, ...) stl::log::log(P_SOURCEINFO, 0, channel, format, __VA_ARGS__)

namespace stl
{
    struct source_info
    {
        const char* const file;
        const char* const function;
        const int line;
    };
    
    class logger
    {
    public:
        virtual ~logger() {}
        
        //replace format and args with fixed_string?
        virtual void log(const stl::source_info& source_info, int level, const char* channel, const char* format, va_list args) = 0;
    };
    
    //0 = fatal, 1 = error, 2 = warning, 3 = info, 4 = debug
    namespace log
    {
        void set_logger(logger* logger, int i);
        void log(const stl::source_info& source_info, int level, const char* channel, const char* format, ...);
    };
};