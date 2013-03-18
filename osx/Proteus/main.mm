#import <Foundation/Foundation.h>

#include <GLEW/glew.h>
#include <GLFW/GLFW.h>
#include <GLM/glm.hpp>

#include <string>

#include "SceneGraphSystem.h"

using namespace Proteus;

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    SceneGraphSystem sgs;
    
    SceneGraphSystem::id_t id = sgs.create_sg();
    SceneGraphSystem::id_t id2 = sgs.create_sg();
    SceneGraphSystem::id_t id3 = sgs.create_sg();
    sgs.get(id3).add_node(glm::vec3(1,2,3), glm::quat());
    sgs.destroy_sg(id2);
    SceneGraphSystem::id_t id4 = sgs.create_sg();
    return 0;
}
