#include "mutex.h"


stl::mutex::mutex() : _mutex(PTHREAD_MUTEX_INITIALIZER)
{
}

stl::mutex::~mutex()
{
    pthread_mutex_destroy(&_mutex);
}

void stl::mutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

bool stl::mutex::try_lock()
{
    return pthread_mutex_trylock(&_mutex) == 0;
}

void stl::mutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}
