#ifndef UI_H
#define UI_H

#include "headers.hpp"

class Scene;

class Ui{
private:
    Scene* scene;
    int lightListIndex = 0;
public:
    Ui(){};
    ~Ui();
    void load(GLFWwindow* _window);
    void render(Scene* _scene);
    void lightParams();

};

#endif