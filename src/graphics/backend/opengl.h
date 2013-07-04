#pragma once

#include "stl/platform.h"

#ifdef P_PLATFORM_APPLE
    #include <GLEW/glew.h>
    #include <GLFW/glfw.h>
#elif P_PLATFORM_WIN
    #include <GL/glew.h>
    #include <GL/glfw.h>
#endif