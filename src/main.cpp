
#include "headers.hpp"

#include <iostream>
// Local includes
#include "mainLoop.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include <glm/glm.hpp>

int main(int argc, char* argv[]) {
    
    int windowWidth = 1200;
    int windowHeight = 800;

    //init the interface/camera/scene
    Ui interface{};
    Camera cam{glm::vec3{0,4,-8}, 50.0f, windowWidth, windowHeight};


    // ####### we setup the scene by adding objects/lights #########
    Scene scene{cam};
    // enable SSAO for this scene
    scene.setSSAO(true).setExposure(1.0);

    // create a grid of lights for the scene
    PointLight light{{0,0,0},{0.2,0.2,0.2}};

    int liS = 10; //size of grid
    int liNum = 4; // 4*4 lights
    std::vector<PointLight> lights = std::vector(liNum*liNum,light);
    //Create our lights
    float liStep = liS/liNum;
    for(int i=0; i<liNum*liNum;i++){
        lights[i].setPosition({-liS/2+(i%(int)liNum)*liStep*2,3.5,-liS/2 +(int)(i/liNum)*liStep*2});
        scene.addLight(lights[i]);
    }

    DistantLight light3{glm::vec3{-50,25,-40},glm::vec3{0.8f}};
    light3.enableShadowMap(4096,10.0f);

    scene.addLight(light3);

    //create a cubemap and add it to the scene
    CubeMap cubemap{"textures/cubemaps/yokohama/"};
    scene.setCubeMap(cubemap);

    Cube cube0{1.0f};
    cube0.setPosition({1.1f,1.5f,0.0f}).setDiffuse({0.0f,1.0f,0.0f}).setSpecular(glm::vec3{0.9})
        .setShaderType(PHONG);

    Cube cube1{1.0f};
    cube1.setPosition({0.0f,1.5f,0.0f}).setAlbedo({0.0f,1.0f,0.0f}).setRoughness(0.4).setMetallic(0.0)
        .setShaderType(PBR);


    Cube cube4(1.0f);
    cube4.setPosition({-2.5f,1.5f,-2.5f})
                .setTexAlbedo("textures/tiles/basecolor.jpg")
                .setTexRoughness("textures/tiles/roughness.jpg")
                .setTexHeight("textures/tiles/height.png").setShaderType(PBR);

    scene.addModel(cube0).addModel(cube1).addModel(cube4);

    UVSphere sphere1(1.0,25,20);
    sphere1.setPosition({3.5,1.5,3.5}).setRotation(-90,{1,0,0}).
    setAlbedo({1,0,0}).setRoughness(0.2).setMetallic(0.95).setShaderType(PBR).enableTesselation(HIGH);
    scene.addModel(sphere1);

    Plane plane1{{20,20},30,30};
    plane1.setRotation(-90,{1,0,0}).setTexAlbedo("textures/stoneWall/diffuse.png")
                .setTexRoughness("textures/stoneWall/roughness.png")
                .setTexHeight("textures/stoneWall/height.png").displacementStrength(0.1f)
                .setTexNormal("textures/stoneWall/normal.png")
                .setTexAO("textures/stoneWall/ao.png")
                .setTexScaling({4,4}).enableTesselation(LOW).setShaderType(PBR);
    scene.addModel(plane1);

    Cube wall(1.0f);
    wall.setScale({7.0f,3.5f,0.3f}).setRotation(45,{0,1,0}).setPosition({-4,0,-2});

    scene.addModel(wall);//.addModel(ground);

    FileModel teapot{"models/teapot.obj",SMOOTH_NORMAL_ENABLE};
    teapot.setScale(glm::vec3{0.35f}).setPosition({0.0f,2.0f,-1.8f})
       .setAlbedo({1.0f,0.5f,0.0f}).setRoughness(0.1).setMetallic(0.95)
       .enableTesselation(HIGH).setShaderType(PBR);
    scene.addModel(teapot);

    //FileModel acCobra{"models/AC_Cobra/Shelby.obj",SMOOTH_NORMAL_ENABLE};
    //acCobra.setScale(glm::vec3{1.0f}).setPosition({0.0f,2.0f,5.0f});

    //FileModel suzanne{"models/suzanne.obj",SMOOTH_NORMAL_ENABLE};
    //suzanne.setScale(glm::vec3{0.5f}).setPosition({-2.5f,2.0f,-2.0f}).enableTesselation(HIGH).setDiffuse({0.1f,0.1f,0.9f});
   
    //scene.addModel(acCobra).addModel(suzanne);


    // ########## start the render loop, give it the scene/cameras etc.. #########
    MainLoop renderLoop{scene,interface,cam};
    // first, load scene objects to GPU
    scene.load();
    //start the render loop
    renderLoop.run();

    return 0;
}







