#include "scene.hpp"


Scene::Scene(){
    models = {};
    lights = {};
}

//! Load the scene models on GPU before rendering
void Scene::load(){
    for(uint32_t i = 0;i<models.size(); i++){
        std::cout << "loading obj"<<i<<std::endl;
        models[i]->load();
    }
}

//! Render all objects of scene
void Scene::render(Camera& _cam){
    for(uint32_t i = 0;i<models.size(); i++){
        models[i]->render(lights,_cam);
    }
}

//! Add and object to scene
Scene& Scene::addModel(Model& _model){
    models.push_back(&_model);
    return *this;
}

//! Get a specific object of scene 
Model& Scene::getModel(int _index){
    if(_index>=0 && _index<models.size()){
        return *models[_index];
    } else {
        throw std::invalid_argument( "model index out of range" );
    }
}

//! Get all objects of scene
std::vector<Model*>& Scene::getAllModels(){
    return models;
}

//! Add a light to the scene
Scene& Scene::addLight(Light& _light){
    lights.push_back(_light);
    return *this;
}

//! Get a specific light of scene 
Light& Scene::getLight(int _index){
    if(_index>=0 && _index<lights.size()){
        return lights[_index];
    } else {
        throw std::invalid_argument( "light index out of range" );
    }
}