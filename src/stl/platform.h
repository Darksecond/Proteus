#pragma once

#ifdef __APPLE__
    #define P_PLATFORM apple
    #define P_PLATFORM_APPLE
#elif _WIN32
    #define P_PLATFORM win
    #define P_PLATFORM_SPECIFIC win32
    #define P_PLATFORM_WIN
    #define P_PLATFORM_WIN32
#elif _WIN64
    #define P_PLATFORM win
    #define P_PLATFORM_SPECIFIC win64
    #define P_PLATFORM_WIN
    #define P_PLATFORM_WIN64
#else
    #error Unknown platform
#endif

//TODO support windows!
#ifdef P_PLATFORM_WIN
    #error Platform not (yet) supported
#endif