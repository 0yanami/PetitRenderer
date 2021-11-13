#include "scene.hpp"

Scene::Scene() {
    models = {};
    lights = {};
}

//! Load the scene models on GPU before rendering
void Scene::load() {
    // create depth buffers for shadow map enabled lights
    for (uint32_t i = 0; i < lights.size(); i++) {
        if (lights[i]->hasShadowMap()) {
            DistantLight* li = dynamic_cast<DistantLight*>(lights[i]);
            std::cout << "creating depth buffer\n";
            li->createDepthBuffer();
        }
    }
    if (cubeMap != nullptr) cubeMap->load();
    for (uint32_t i = 0; i < models.size(); i++) {
        models[i]->load();
    }
}

//! render cubeMap, this is the first object to render
void Scene::renderCubeMap(Camera& _cam) {
    if (cubeMap != nullptr) cubeMap->render(_cam);
}

//! render depth map for each shadow map enabled light in scene
void Scene::depthMaps_pass(Camera& _cam) {
    for (uint32_t i = 0; i < lights.size(); i++) {
        if (lights[i]->hasShadowMap()) {
            DistantLight* li = dynamic_cast<DistantLight*>(lights[i]);
            Shader sh = {"shaders/depthMap.vert", "shaders/depthMap.frag"};
            
            sh.use();
            sh.setMat4("vp", li->getLightSpacematrix());

            uint32_t res = li->getShadowMapRes();
            glViewport(0, 0, res, res);
            glBindFramebuffer(GL_FRAMEBUFFER, li->getFbo());
            glClear(GL_DEPTH_BUFFER_BIT);

            renderModelsForDepth(sh);
            
            // reset
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, _cam.getResWidth(), _cam.getResHeight());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
}

void Scene::SSAO_pass(){

    //creer les 2 buffers de texture :
    // ssao
    // ssaoblur

    //get la depth map
    // generer la texture SSAO
    // generer la texture SSAOBlur

    Shader sh = {"shaders/depthMap.vert", "shaders/depthMap.frag"};

    //renderModelsForDepth(sh);
}

//! Render all objects of scene
void Scene::renderModels(Camera& _cam) {
    for (uint32_t i = 0; i < models.size(); i++) {
        models[i]->render(lights, _cam);
    }
}

void Scene::renderModelsForDepth(Shader& _shader) {
    for (uint32_t i = 0; i < models.size(); i++) {
        models[i]->renderForDepth(_shader);
    }
}

//! Add and object to scene
Scene& Scene::addModel(Model& _model) {
    models.push_back(&_model);
    return *this;
}

//! Add a light to the scene
Scene& Scene::addLight(Light& _light) {
    lights.push_back(&_light);
    return *this;
}

Scene& Scene::setCubeMap(CubeMap& _cubeMap) {
    cubeMap = &_cubeMap;
    return *this;
}
