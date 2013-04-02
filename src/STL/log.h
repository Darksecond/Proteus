#pragma once

#define P_SOURCEINFO stl::SourceInfo{__FILE__, __FUNCTION__, __LINE__}

namespace stl
{
    struct SourceInfo
    {
        const char* const file;
        const char* const function;
        const int line;
    };
    
    namespace Log
    {
        //addWriter(...)
        //debug(...)
        //info(...)
        //warning(...)
        //error(...)
        //fatal(...)
    };
};