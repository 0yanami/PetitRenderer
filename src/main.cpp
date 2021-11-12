
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
    PointLight light1{glm::vec3{0,0,4},glm::vec3{1.0f}};
    PointLight light2{glm::vec3{0,3,-5},glm::vec3{1.5f}};
    DistantLight light3{glm::vec3{-100,40,-80},glm::vec3{0.9f,0.85f,0.8f}};
    // create a scene
    Scene baseScene{};

    // add object to scene
    Cube cube1(1.0f);
    Cube cube2(1.0f);
    Cube cube3(1.0f);
    Cube ground(1.0f);

    //add a cubemap
    CubeMap cubemap{"textures/cubemaps/tantolunden5/"};

    FileModel teapot{"models/teapot.obj",SMOOTH_NORMAL_ENABLE};
    //FileModel gtx{"models/gtx/GTX_1070TI.obj",SMOOTH_NORMAL_DISABLE};
    //FileModel suzanne{"models/suzanne.obj",SMOOTH_NORMAL_ENABLE};

    cube1.setTextures("textures/containerDiffuse.png","textures/containerSpecular.png").setPosition(glm::vec3{2.5,1.8,0});

    cube2.setPosition(glm::vec3{0,1.5,0}).setDiffuse(glm::vec3 {1,0.6,0.4});

    cube3.setPosition(glm::vec3{-2.5,1.5,0})
    .setTextures("textures/tilesDiffuse.jpg","textures/tilesSpecular.jpg","textures/tilesHeight.png");

    ground.setScale(glm::vec3{50,0.5,50}).setPosition(glm::vec3{0,0,0}).setSpecular(glm::vec3{0.0f});

    teapot.setScale(glm::vec3{0.35f}).setPosition(glm::vec3{0,0.5,-1.5})
        .setDiffuse(glm::vec3{0.9,0.2,0.2}).enableTesselation().setSpecular(glm::vec3{0.5});
//
    ////gtx.setScale(glm::vec3{4.0f}).setPosition(glm::vec3{0,-4,1.3});
//
    //suzanne.setScale(glm::vec3{0.5}).setPosition(glm::vec3{0,-2,-2}).enableTesselation();

    baseScene.addModel(cube1).addModel(cube2).addModel(cube3).addModel(ground).addModel(teapot);

    light3.enableShadowMap(4096,15);

    baseScene.addLight(light3);

    baseScene.setCubeMap(cubemap);

    // start render loop, open GLFW window
    MainLoop renderLoop{baseScene,interface,cam};
    //load scene to GPU
    baseScene.load();
    //start render loop
    renderLoop.run();

    return 0;
}







