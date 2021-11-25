
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
    Camera cam{glm::vec3{0,4,-8}, 50.0f, windowWidth, windowHeight};
    //Create a light
    PointLight light1{glm::vec3{3,2,-4},glm::vec3{0.1f,1.0f,0.6f}};
    PointLight light2{glm::vec3{0,3,-5},glm::vec3{1.5f}};
    DistantLight light3{glm::vec3{-100,50,-80},glm::vec3{0.6f}};
    //DistantLight light4{glm::vec3{-100,50,-20},glm::vec3{0.3f}};
    // create a scene
    Scene baseScene{cam};

    // add object to scene
    Cube cube1(1.0f);
    Cube cubelight(0.1f);
    Cube cube2(1.0f);
    Cube cube3(1.0f);
    Cube ground(1.0f);
    Cube wall(1.0f);

    //add a cubemap
    CubeMap cubemap{"textures/cubemaps/tantolunden5/"};

    FileModel teapot{"models/teapot.obj",SMOOTH_NORMAL_ENABLE};
    FileModel acCobra{"models/AC_Cobra/Shelby.obj",SMOOTH_NORMAL_ENABLE};
    FileModel suzanne{"models/suzanne.obj",SMOOTH_NORMAL_ENABLE};

    cube1.setTextures("textures/containerDiffuse.png","textures/containerSpecular.png").setPosition({2.5f,1.8f,0.0f});

    cube2.setPosition({0.0f,1.5f,0.0f}).setDiffuse({1.0f,0.6f,0.4f});

    cube3.setPosition({-2.5f,1.5f,0.0f})
    .setTextures("textures/tilesDiffuse.jpg","textures/tilesSpecular.jpg","textures/tilesHeight.png");

    ground.setScale({20.0f,0.5f,20.0f}).setSpecular(glm::vec3{0.0f});

    wall.setScale({7.0f,3.5f,0.3f}).setRotation(45,{0,1,0}).setPosition({-4,0,-2});

    teapot.setScale(glm::vec3{0.35f}).setPosition({0.0f,2.0f,-1.8f})
        .setDiffuse({0.9f,0.2f,0.2f}).enableTesselation(MEDIUM).setSpecular(glm::vec3{0.5f});

    acCobra.setScale(glm::vec3{1.0f}).setPosition({0.0f,2.0f,5.0f});

    suzanne.setScale(glm::vec3{0.5f}).setPosition({-2.5f,2.0f,-2.0f}).enableTesselation(HIGH).setDiffuse({0.1f,0.1f,0.9f});

    cubelight.setPosition({3,2,-4});

    baseScene.addModel(cube1).addModel(cube2).addModel(cube3).addModel(wall).addModel(ground).addModel(teapot);
    baseScene.addModel(acCobra).addModel(suzanne);
    light3.enableShadowMap(4096,10.0f);

    //light4.enableShadowMap(2048,10.0f);

    baseScene.addLight(light3).addLight(light1);

    baseScene.setCubeMap(cubemap);

    // start render loop, open GLFW window
    MainLoop renderLoop{baseScene,interface,cam};
    //baseScene.enableSSAO();
    //load scene to GPU
    baseScene.load();
    //start render loop
    renderLoop.run();

    return 0;
}







