#pragma once

#define P_SOURCEINFO STL::SourceInfo{__FILE__, __LINE__}

namespace STL
{
    struct SourceInfo
    {
        const char* const file;
        const int line;
    };
};