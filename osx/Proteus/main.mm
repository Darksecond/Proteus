#import <Foundation/Foundation.h>

#include <string>
#include <iostream>
#include <GLFW/glfw.h>

#include "STL/string_hash.h"
#include "STL/memory.h"

using namespace Proteus;

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

struct alignas(128) bigalign
{
    uint64_t i[2];
};

int main(int argc, char* argv[])
{
    STL::HeapArea area(64*1024*1024); //64 megabytes
    STL::LinearAllocator alloc(area.start(), area.end());
    int* a = P_NEW(alloc, int, 3);
    P_DELETE(alloc, a);
    alloc.reset();
}
