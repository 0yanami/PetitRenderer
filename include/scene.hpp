#ifndef SCENE_H
#define SCENE_H

#include <stdexcept>

#include "model.hpp"
#include "headers.hpp"
#include "camera.hpp"
#include "light.hpp"


class Scene{
    
private:
    std::vector<Model*> models;
    std::vector<Light*> lights;
    CubeMap* cubeMap = nullptr;

public:
    Scene();

    void load();
    void renderCubeMap(Camera& _cam);
    void renderDepthMaps(Camera& _cam);
    void renderModels(Camera& _cam);
    //! render pass for depth map
    void renderModelsForDepth(Shader& _shader);

    Scene& addModel(Model& _model);
    Scene& addLight(Light& _light);
    Scene& setCubeMap(CubeMap& _cubeMap);
    
};

#endif