#ifndef LIGHT_H
#define LIGHT_H

#include "camera.hpp"
#include "headers.hpp"
#include "shader.hpp"

class Light {
   protected:
    glm::vec3 position;

    glm::vec3 diffuse;
    glm::vec3 specular;

    // falloff parameters
    float ambiantStrength;
    float constant;
    float linear;
    float quadratic;

   public:
    Light(){};

    void setDiffuse(glm::vec3 _color) { diffuse = _color; }
    void setAmbiantStrength(float _strength) { ambiantStrength = _strength; }
    void setSpecular(glm::vec3 _color) { specular = _color; }
    void setConstant(float _val) { constant = _val; }
    void setLinear(float _val) { linear = _val; }
    void setQuadratic(float _val) { quadratic = _val; }

    glm::vec3 getPos() { return position; }
    glm::vec3 getAmbiant() { return diffuse * glm::vec3(ambiantStrength); }
    glm::vec3 getDiffuse() { return diffuse; }
    glm::vec3 getSpecular() { return specular; }

    float getConstant() { return constant; }
    float getLinear() { return linear; }
    float getQuadratic() { return quadratic; }

    virtual bool hasShadowMap() = 0;
};

class PointLight : public Light {
   public:
    PointLight(glm::vec3 _position, glm::vec3 _color) {
        position = _position;

        diffuse = _color;
        ambiantStrength = 0.25f;
        specular = glm::vec3(1.0f, 1.0f, 1.0f);

        constant = 1.0f;
        linear = 0.22f;
        quadratic = 0.2f;
    }

    bool hasShadowMap() {return false;}
};

class DistantLight : public Light {
   private:
    // shadow map
    bool shadowMapEnabled = false;
    uint32_t depthTexture;
    uint32_t textureRes;
    uint32_t fbo;

    glm::mat4 lightSpaceMatrix;

    Shader depthShader;

   public:
    DistantLight(glm::vec3 _position, glm::vec3 _color) {
        position = _position;

        diffuse = _color;
        ambiantStrength = 0.25f;
        specular = glm::vec3(1.0f, 1.0f, 1.0f);

        constant = -1.0f;
        linear = -1.0f;
        quadratic = -1.0f;

    }

    DistantLight& enableShadowMap(int _resolution,float _domainSize) {
        shadowMapEnabled = true;
        textureRes = _resolution;
        float d = _domainSize;

        glm::mat4 projection =
                glm::ortho(-d, d, -d, d, 0.1f, d*2);
        glm::mat4 view = glm::lookAt(glm::normalize(position)*(d/2), glm::vec3(0.0f),
                                         glm::vec3(0.0, 1.0, 0.0));

        lightSpaceMatrix = projection * view;

        return *this;
    }

    void createDepthBuffer() {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        // create depth texture
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureRes,
                     textureRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture,
                             0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        depthShader = {"shaders/depthMap.vert", "shaders/depthMap.frag"};
    }

    uint32_t getDepthTexture() { return depthTexture; }

    bool hasShadowMap() { return shadowMapEnabled; }

    Shader& getShader() { return depthShader; }

    uint32_t getShadowMapRes() { return textureRes; }

    uint32_t getFbo(){return fbo;}

    glm::mat4 getLightSpacematrix(){
        return lightSpaceMatrix;
    }
};

#endif