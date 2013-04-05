#include "log.h"

static stl::Logger* loggers[8] = {nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr};

void stl::log::set_logger(Logger* l, int i)
{
    loggers[i] = l;
}