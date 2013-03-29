#import <Foundation/Foundation.h>

#include <string>
#include <iostream>

#include "STL/memory.h"

using namespace Proteus;

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    STL::Allocator& someArena = STL::defaultAllocator();
    int* a = P_NEW(someArena, int, 3);
    P_DELETE(someArena, a);
    int* b = P_NEW_ARRAY(someArena, int[3]);
    P_DELETE_ARRAY(someArena, b);
    return 0;
}
