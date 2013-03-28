#pragma once

#define P_SOURCEINFO Proteus::STL::SourceInfo{__FILE__, __LINE__}

namespace Proteus
{
    namespace STL
    {
        struct SourceInfo
        {
            const char* file;
            int line;
        };
    };
};