#include "scene.hpp"


Scene::Scene(){
    models = {};
    lights = {};
}

//! Load the scene models on GPU before rendering
void Scene::load(){
    if(cubeMap != nullptr)
        cubeMap->load();
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->load();
    }
}

//! Render all objects of scene
void Scene::render(Camera& _cam){
    if(cubeMap != nullptr)
        cubeMap->render(_cam);
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->render(lights,_cam);
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
