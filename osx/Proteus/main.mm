#import <Foundation/Foundation.h>

#include <GLEW/glew.h>
#include <GLFW/GLFW.h>
#include <GLM/glm.hpp>

#include <string>

#include "Application.h"

using namespace Proteus;

static std::string ResourceDirectory()
{
    NSString* path = [[NSBundle mainBundle] resourcePath];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

int main(int argc, char* argv[])
{
    Application app;
    world_id_t world_id = app.create_world();
    World& sgs = app.get_world(world_id);
    
    unit_id_t id = sgs.create_sg();
    unit_id_t id2 = sgs.create_sg();
    unit_id_t id3 = sgs.create_sg();
    sgs.get(id3).scenegraph.add_node(glm::vec3(1,2,3), glm::quat());
    sgs.destroy_sg(id2);
    unit_id_t id4 = sgs.create_sg();
    return 0;
}
