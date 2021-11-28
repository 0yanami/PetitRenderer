
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
    scene.setSSAO(true).setExposure(0.7);

    //Create our lights
    PointLight light1{glm::vec3{3,2,-4},glm::vec3{2.0f,2.0f,2.0f}};
    PointLight light2{glm::vec3{0,3,2},glm::vec3{2.0f,2.0f,2.0f}};
    // a distant light with 4k shadowmap enabled
    DistantLight light3{glm::vec3{-50,25,-40},glm::vec3{1.3f}};
    light3.enableShadowMap(4096,10.0f);

    scene.addLight(light2).addLight(light1).addLight(light3);//.addLight(light3);

    //create a cubemap and add it to the scene
    //CubeMap cubemap{"textures/cubemaps/yokohama/"};
    //scene.setCubeMap(cubemap);
    
    // to represent the light as a cube
    Cube cubelight1(3.0f);
    cubelight1.setPosition(light3.getPos());

    Cube cubelight2(.3f);
    cubelight2.setPosition(light1.getPos());

    Cube cubelight3(.3f);
    cubelight3.setPosition(light2.getPos());

    scene.addModel(cubelight1).addModel(cubelight2).addModel(cubelight3);
    //basic colored cube
    Cube cube1{1.0f};
    cube1.setPosition({0.0f,1.5f,0.0f}).setDiffuse({0.1f,0.8f,0.5f}).setSpecular(glm::vec3{0.8});

    // basic cube with textures
    Cube cube2(1.0f);
    cube2.setTexDiffuse("textures/wood/basecolor.png").setTexSpecular("textures/wood/roughness.png")
    .setPosition({2.5f,1.8f,0.0f});

    // cube with texture + bump map tessellation
    Cube cube3(1.0f);
    cube3.setPosition({-2.5f,1.5f,0.0f})
                .setTexDiffuse("textures/stoneWall/diffuse.png")
                .setTexSpecular("textures/stoneWall/roughness.png")
                .setTexHeight("textures/stoneWall/height.png").displacementStrength(0.1f)
                .setTexNormal("textures/stoneWall/normal.png")
                .setTexAO("textures/stoneWall/ao.png");
                
    Cube cube4(1.0f);
    cube4.setPosition({-2.5f,1.5f,-2.5f})
                .setTexDiffuse("textures/tiles/basecolor.jpg")
                .setTexSpecular("textures/tiles/roughness.jpg")
                .setTexHeight("textures/tiles/height.png");
                


    scene.addModel(cube1).addModel(cube2).addModel(cube3).addModel(cube4);

    UVSphere sphere1(1.0,30,20);
    sphere1.setPosition({0,4,0}).setTexDiffuse("textures/tiles/basecolor.jpg")
                .setTexSpecular("textures/tiles/roughness.jpg");
    scene.addModel(sphere1);

    Plane plane1{{1,1},40,40};
    plane1.setRotation(-90,{1,0,0}).setScale(glm::vec3{15.0f}).setTexDiffuse("textures/stoneWall/diffuse.png")
                .setTexSpecular("textures/stoneWall/roughness.png")
                .setTexHeight("textures/stoneWall/height.png").displacementStrength(0.07f)
                .setTexNormal("textures/stoneWall/normal.png")
                .setTexAO("textures/stoneWall/ao.png").setTexScaling({8,8}).enableTesselation(HIGH);
    scene.addModel(plane1);

    //cube with texture + bump map + normal map
    //TODO:

    //Cube ground(1.0f);
    //ground.setScale({20.0f,0.5f,20.0f}).setSpecular(glm::vec3{0.0f}).setDiffuse(glm::vec3{0.5f});

    Cube wall(1.0f);
    wall.setScale({7.0f,3.5f,0.3f}).setRotation(45,{0,1,0}).setPosition({-4,0,-2});

    scene.addModel(wall);//.addModel(ground);

    FileModel teapot{"models/teapot.obj",SMOOTH_NORMAL_ENABLE};
    teapot.setScale(glm::vec3{0.35f}).setPosition({0.0f,2.0f,-1.8f})
       .setDiffuse({1.0f,0.5f,0.0f}).enableTesselation(HIGH).setSpecular(glm::vec3{0.8f});
    scene.addModel(teapot);
    //FileModel acCobra{"models/AC_Cobra/Shelby.obj",SMOOTH_NORMAL_ENABLE};
    //acCobra.setScale(glm::vec3{1.0f}).setPosition({0.0f,2.0f,5.0f});

    //FileModel suzanne{"models/suzanne.obj",SMOOTH_NORMAL_ENABLE};
    //suzanne.setScale(glm::vec3{0.5f}).setPosition({-2.5f,2.0f,-2.0f}).enableTesselation(HIGH).setDiffuse({0.1f,0.1f,0.9f});
   
    //scene.addModel(acCobra).addModel(suzanne).addModel(teapot);


    // ########## start the render loop, give it the scene/cameras etc.. #########
    MainLoop renderLoop{scene,interface,cam};
    // first, load scene objects to GPU
    scene.load();
    //start the render loop
    renderLoop.run();

    return 0;
}







