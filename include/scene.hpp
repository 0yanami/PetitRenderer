#ifndef SCENE_H
#define SCENE_H

#include <stdexcept>

#include "headers.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "light.hpp"


class Scene{
    
private:
    std::vector<Model*> models;
    std::vector<Light> lights;

public:
    Scene();

    void load();
    void render(Camera& _cam);

    Scene& addModel(Model& _model);
    Scene& addLight(Light& _light);
    

    Model& getModel(int _index);
    std::vector<Model*>& getAllModels();

    Light& getLight(int _index);
};

#endif