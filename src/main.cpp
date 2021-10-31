
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
    Camera cam{glm::vec3{0,0,5}, 55.0f, windowWidth, windowHeight};
    //Create a light
    Light light1{glm::vec3{2.0},glm::vec3{1.0}};
    // create a scene
    Scene baseScene{};

    // add object to scene
    Cube cube1(1.0);
    Cube cube2(1.0);

    cube2.setScale(glm::vec3{1.2}).setRotation(40.0,glm::vec3{0,0.5,0}).setPosition(glm::vec3{2.5,0,0});

    baseScene.addModel(cube1).addModel(cube2).addLight(light1);



    // start render loop, open GLFW window
    MainLoop renderLoop{baseScene,interface,cam};
    //load scene to GPU
    baseScene.load();
    // init prameters of loop
    renderLoop.setWindowSize(800,600);
    //start render loop
    renderLoop.run();

    return 0;
}







