#include "console_logger.h"
#include "stl/string/fixed_string.h"

#include <iostream>

void stl::console_logger::log(const stl::source_info& source_info, int level, const char* channel, const char* format, va_list args)
{
    stl::fixed_string<512> log_message;
    log_message.append_fmt("[%i][%s][%s:%i] ", level, channel, source_info.file, source_info.line);
    log_message.append_fmt_v(format, args);
    
    std::cout << log_message.c_str() << std::endl;
}