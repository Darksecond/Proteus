#import <Foundation/Foundation.h>

#include <string>
#include <iostream>
#include <GLFW/glfw.h>
#include <string.h>

#include "stl/logging/log.h"
#include "stl/logging/console_logger.h"
#include "stl/hash.h"
#include "stl/memory.h"
#include "stl/string/string_hash.h"
#include "stl/string/fixed_string.h"
#include "stl/memory/linear_allocator.h"
#include "stl/memory/simple_arena.h"

#include "stl/containers/dynamic_array.h"
#include "stl/containers/freelist.h"

#include "stl/filesystem/root.h"
#include "stl/filesystem/fs_archive.h"
#include "stl/filesystem/file.h"
#include "stl/filesystem/modes.h"

#include "stl/threading/thread.h"
#include "stl/threading/thread_local_storage.h"

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

void test_thread_function(const stl::thread&)
{
    int i;
    i = 3;
    std::cout << "test" << std::endl;
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
    
    stl::dynamic_array<int> test_array(&arena);
    std::cout << test_array.size() << std::endl;
    
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
    
    stl::console_logger console_logger;
    stl::log::set_logger(&console_logger, 0);
    P_LDEBUG("main", "Hello, World! %i", 123);
    
    stl::root root(&arena, 8);
    stl::fs_archive fsa("/etc", &arena);
    root.mount(&fsa);
    stl::file* test_file = root.open("hosts", stl::fs_modes::in);
    std::cout << "Test file size: " << test_file->total_size() << std::endl;
    root.close(test_file);
    
    stl::thread t;
    t.create("test", &test_thread_function);
    t.join();
    
    char* f_list_array = P_NEW(arena, char, 1024);
    stl::freelist f(f_list_array, f_list_array+1024, 16);
    void* f_addr1 = f.pop();
    void* f_addr2 = f.pop();
    P_LDEBUG("freelist", "faddr1: 0x%x, should be: 0x%x", f_addr1, f_list_array);
    P_LDEBUG("freelist", "faddr2: 0x%x, should be: 0x%x", f_addr2, f_list_array+16);
    P_DELETE(arena, f_list_array);
}