#import <Foundation/Foundation.h>

#include <string>
#include <iostream>
#include <GLFW/glfw.h>
#include <string.h>

#include "stl/hash.h"
#include "stl/memory.h"
#include "stl/string/string_hash.h"
#include "stl/string/fixed_string.h"
#include "stl/memory/linear_allocator.h"

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    stl::heap_area area(64*1024*1024); //64 megabytes
    stl::linear_allocator alloc(area.start(), area.end());
    int* a = P_NEW(alloc, int, 3);
    P_DELETE(alloc, a);
    alloc.reset();
    
    std::cout << stl::Hash::hash_fnv1a("test") << std::endl;
    
    std::cout << stl::string_hash("test") << std::endl;
    
    std::string test("test");
    std::cout << stl::string_hash(test.c_str()) << std::endl;
    std::cout << stl::Hash::hash_fnv1a(test.c_str()) << std::endl;
    
    stl::fixed_string<512> fixed_string;
    fixed_string.append("some test string");
    fixed_string.append_fmt(" test: %i", 123);
    std::cout << fixed_string.c_str() << std::endl;
}
