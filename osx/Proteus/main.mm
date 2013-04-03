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
#include "stl/memory/simple_arena.h"

#include "stl/containers/dynamic_array.h"

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    stl::heap_area area(64*1024*1024); //64 megabytes
    stl::linear_allocator alloc(area.start(), area.end());
    stl::simple_arena<stl::linear_allocator> arena(&alloc);
    int* a = P_NEW(arena, int, 3);
    P_DELETE(arena, a);
    alloc.reset();
    
    std::cout << stl::hash::hash_fnv1a("test") << std::endl;
    
    std::cout << stl::string_hash("test") << std::endl;
    
    std::string test("test");
    std::cout << stl::string_hash(test.c_str()) << std::endl;
    std::cout << stl::hash::hash_fnv1a(test.c_str()) << std::endl;
    
    stl::fixed_string<512> fixed_string;
    fixed_string.append("some test string");
    fixed_string.append_fmt(" test: %i", 123);
    std::cout << fixed_string.c_str() << std::endl;
    
    stl::dynamic_array<int> dynamic_array(&arena, 23);
    dynamic_array.add(12);
    dynamic_array.add(9);
    dynamic_array.add(10);
    dynamic_array.add(79);
    dynamic_array.erase(1);
    std::cout << dynamic_array.size() << " " << dynamic_array.capacity() << " " << dynamic_array[1] << std::endl;
    
    std::cout << "elements in dynamic array:" << std::endl;
    for(auto& i : dynamic_array)
    {
        std::cout << i << std::endl;
    }
}
