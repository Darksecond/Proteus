#import <Foundation/Foundation.h>

#include <string>
#include <iostream>
#include <GLFW/glfw.h>
#include <string.h>

#include "STL/hash.h"
#include "STL/memory.h"
#include "STL/String/Stringhash.h"
#include "STL/String/FixedString.h"

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    STL::HeapArea area(64*1024*1024); //64 megabytes
    STL::LinearAllocator alloc(area.start(), area.end());
    int* a = P_NEW(alloc, int, 3);
    P_DELETE(alloc, a);
    alloc.reset();
    
    std::cout << STL::Hash::hash_fnv1a("test") << std::endl;
    
    std::cout << STL::StringHash("test") << std::endl;
    
    std::string test("test");
    std::cout << STL::StringHash(test.c_str()) << std::endl;
    std::cout << STL::Hash::hash_fnv1a(test.c_str()) << std::endl;
    
    STL::FixedString<512> fixed_string;
    fixed_string.append("some test string");
    fixed_string.append_fmt(" test: %i", 123);
    std::cout << fixed_string.c_str() << std::endl;
}
