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
    return 0;
}
