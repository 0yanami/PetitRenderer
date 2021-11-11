#include "scene.hpp"


Scene::Scene(){
    models = {};
    lights = {};
}

//! Load the scene models on GPU before rendering
void Scene::load(){
    // create depth buffers for shadow map enabled lights
    for(uint32_t i = 0; i<lights.size();i++){
        if(lights[i].hasShadowMap()){
            lights[i].createDepthBuffer();
        }
    }
    if(cubeMap != nullptr)
        cubeMap->load();
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->load();
    }
}

//! render cubeMap, this is the first object to render
void Scene::renderCubeMap(Camera& _cam){
    if(cubeMap != nullptr)
        cubeMap->render(_cam);
}

//! render depth map for each shadow map enabled light in scene
void Scene::renderDepthMaps(Camera& _cam){
    for(uint32_t i = 0; i<lights.size();i++){
        if(lights[i].hasShadowMap()){
            lights[i].renderDepthMap(*this,_cam);
        }
    }
}

//! Render all objects of scene
void Scene::renderModels(Camera& _cam){
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->render(lights,_cam);
    }
}

void Scene::renderModelsForDepth(Shader& _shader){
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->renderForDepth(_shader);
    }
}

//! Add and object to scene
Scene& Scene::addModel(Model& _model){
    models.push_back(&_model);
    return *this;
}


//! Add a light to the scene
Scene& Scene::addLight(Light& _light){
    lights.push_back(_light);
    return *this;
}

Scene& Scene::setCubeMap(CubeMap& _cubeMap){
    cubeMap = &_cubeMap;
    return *this;
}
