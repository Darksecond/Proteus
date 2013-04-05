#pragma once

#define P_SOURCEINFO stl::source_info{__FILE__, __FUNCTION__, __LINE__}

namespace stl
{
    struct source_info
    {
        const char* const file;
        const char* const function;
        const int line;
    };
    
    class Logger;
    
    namespace log
    {
        void set_logger(Logger* logger, int i);
        
        //debug(...)
        //info(...)
        //warning(...)
        //error(...)
        //fatal(...)
    };
};