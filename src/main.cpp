
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
    FileModel acCobra{"models/AC_Cobra/Shelby.obj",SMOOTH_NORMAL_ENABLE};
    FileModel suzanne{"models/suzanne.obj",SMOOTH_NORMAL_ENABLE};

    cube1.setTextures("textures/containerDiffuse.png","textures/containerSpecular.png").setPosition(2.5f,1.8f,0.0f);

    cube2.setPosition(0.0f,1.5f,0.0f).setDiffuse(1.0f,0.6f,0.4f);

    cube3.setPosition(-2.5f,1.5f,0.0f)
    .setTextures("textures/tilesDiffuse.jpg","textures/tilesSpecular.jpg","textures/tilesHeight.png");

    ground.setScale(50.0f,0.5f,50.0f).setSpecular(0.0f);

    teapot.setScale(0.35f).setPosition(0.0f,2.0f,-1.8f)
        .setDiffuse(0.9f,0.2f,0.2f).enableTesselation(MEDIUM).setSpecular(0.5f);

    acCobra.setScale(1.0f).setPosition(0.0f,3.0f,5.0f).enableTesselation(LOW);

    suzanne.setScale(0.5f).setPosition(-2.5f,2.0f,-2.0f).enableTesselation(HIGH).setDiffuse(0.1f,0.1f,0.9f);

    baseScene.addModel(cube1).addModel(cube2).addModel(cube3)
             .addModel(ground).addModel(teapot).addModel(suzanne).addModel(acCobra);

    light3.enableShadowMap(4096,10.0f);

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







