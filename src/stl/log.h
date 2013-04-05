#pragma once

#include <cstdarg>

#define P_SOURCEINFO stl::source_info{__FILE__, __FUNCTION__, __LINE__}

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
        //replace format and args with fixed_string?
        virtual void log(stl::source_info& source_info, int level, const char* channel, const char* format, va_list args) = 0;
    };
    
    namespace log
    {
        void set_logger(logger* logger, int i);
        void log(stl::source_info& source_info, int level, const char* channel, const char* format, ...);
    };
};