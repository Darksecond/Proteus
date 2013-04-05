#pragma once

#include "stl/logging/log.h"

namespace stl
{
    class console_logger : public logger
    {
    public:        
        //replace format and args with fixed_string?
        virtual void log(const stl::source_info& source_info, int level, const char* channel, const char* format, va_list args);
    };
};