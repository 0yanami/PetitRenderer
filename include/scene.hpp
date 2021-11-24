#ifndef SCENE_H
#define SCENE_H

#include <stdexcept>

#include "model.hpp"
#include "headers.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "ssao.hpp"


class Scene{
    
private:
    std::vector<Model*> models;
    std::vector<Light*> lights;

    Camera& cam; 

    SSAO* ssao = nullptr;
    bool ssaoEnabled = false;

    CubeMap* cubeMap = nullptr;

public:
    Scene(Camera& _cam);

    void load();
    void renderCubeMap();
    void SSAO_Pass();
    void depthMaps_pass();
    void renderModels();

    
    Scene& enableSSAO();

    //! Render all models of scene using the same shader
    /**
     * \param _shader The shader to render the models with,
     * only "model" matrix is defined per object.
     **/
    void renderModelsWithShader(Shader& _shader);

    Scene& addModel(Model& _model);
    Scene& addLight(Light& _light);
    Scene& setCubeMap(CubeMap& _cubeMap);
    Scene& setCamera(Camera& _cam);
    
};

#endif