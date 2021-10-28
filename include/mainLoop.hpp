#ifndef RENDER_H
#define RENDER_H

#include <chrono>

#include "scene.hpp"
#include "ui.hpp"
#include "inputs.hpp"
#include "headers.hpp"

class MainLoop {

private:
    Scene activeScene;
    Ui ui;
    Inputs inputs;

    GLFWwindow* window;

    int windowWidth=800;
    int windowHeight=600;
    double deltaTime;
    double lastFrame;

    std::string windowName = "MiniRenderer";

    void updateFpsCounter();

public:
    // setup render loop
    MainLoop(Scene& _scene, Ui& _ui, Inputs& _inputs);

    void setWindowSize(int w,int h);

    void run();
    void shutdown();
};


#endif