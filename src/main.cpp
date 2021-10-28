#include "headers.hpp"

#include <iostream>
// Local includes
#include "mainLoop.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>

int main(int argc, char* argv[]) {
    
    int windowWidth = 800;
    int windowHeight = 600;

    Camera cam{glm::vec3{0,0,-5}, 55.0f, windowWidth, windowHeight};
    Scene baseScene{};
    Ui interface{};
    Inputs inputs{&cam};
    MainLoop loop{baseScene,interface,inputs};
    
    loop.setWindowSize(800,600);

    loop.run();
    loop.shutdown();

    return 0;
}







