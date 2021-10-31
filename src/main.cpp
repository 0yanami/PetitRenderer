
#include "headers.hpp"

#include <iostream>
// Local includes
#include "mainLoop.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include <glm/glm.hpp>

int main(int argc, char* argv[]) {
    
    int windowWidth = 800;
    int windowHeight = 600;

    //tard flemme TODO: à faire
    Ui interface{};

    // initialize camera
    Camera cam{glm::vec3{0,0,6}, 50.0f, windowWidth, windowHeight};
    //Create a light
    Light light1{glm::vec3{0,0,4},glm::vec3{2.0f}};
    // create a scene
    Scene baseScene{};

    // add object to scene
    Cube cube1(1.0f);
    Cube cube2(1.0f);
    //Cube lightpos(0.3f);

    //lightpos.setPosition(glm::vec3{0,2,0});

    cube2.setScale(glm::vec3{1.2}).setRotation(40.0,glm::vec3{0,0.5,0})
        .setPosition(glm::vec3{2.5,0,0});

    cube1.setTexDiffuse("containerDiffuse.png").setTexSpecular("containerSpecular.png");

    baseScene.addModel(cube1).addLight(light1);

    // start render loop, open GLFW window
    MainLoop renderLoop{baseScene,interface,cam};
    //load scene to GPU
    baseScene.load();
    //start render loop
    renderLoop.run();

    return 0;
}







