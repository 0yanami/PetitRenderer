#include "light.hpp"

void DistantLight::createDepthBuffer(){

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // create depth texture
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureRes, textureRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthShader = {"depthMap.vert","depthMap.frag"};
}

void DistantLight::renderDepthMap(Scene &_scene, Camera& _cam){

        glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
        glm::mat4 view = glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        //glm::mat4 lightSpaceMatrix = lightProjection * lightView;
        
        //set depth shader transformations
        depthShader.use();
        depthShader.setMat4("view", view);
        depthShader.setMat4("projection", projection);

        glViewport(0, 0, textureRes, textureRes);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glClear(GL_DEPTH_BUFFER_BIT);

            _scene.renderModelsForDepth(depthShader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, _cam.getResWidth(), _cam.getResHeight());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}