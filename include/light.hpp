#ifndef LIGHT_H
#define LIGHT_H

#include "headers.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "scene.hpp"

class Light{
protected:
    glm::vec3 position;

    glm::vec3 diffuse;
    glm::vec3 specular;

    //falloff parameters
    float ambiantStrength;
    float constant;
    float linear;
    float quadratic;

public:
    Light(){};
    Light(glm::vec3 _position, glm::vec3 _color);

    void setDiffuse(glm::vec3 _color){diffuse = _color;}
    void setAmbiantStrength(float _strength){ambiantStrength = _strength;}
    void setSpecular(glm::vec3 _color){specular = _color;}
    void setConstant(float _val){constant = _val;}
    void setLinear(float _val){linear = _val;}
    void setQuadratic(float _val){quadratic = _val;}

    
    glm::vec3 getPos(){return position;}
    glm::vec3 getAmbiant(){return diffuse*glm::vec3(ambiantStrength);}
    glm::vec3 getDiffuse(){return diffuse;}
    glm::vec3 getSpecular(){return specular;}

    float getConstant(){return constant;}
    float getLinear(){return linear;}
    float getQuadratic(){return quadratic;}

    bool hasShadowMap(){return false;}
    void createDepthBuffer(){}
    void renderDepthMap(Scene& _scene, Camera& _cam){}
};


class DistantLight : public Light {
private:   
    glm::vec3 angle;

    // shadow map 
    bool shadowMapEnabled = false;
    uint32_t  depthTexture;
    uint32_t  textureRes;
    uint32_t fbo;

    Shader depthShader;

public:

    DistantLight(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color){
        position = _position;
        angle = _angle;

        diffuse = _color;
        ambiantStrength = 0.25f;
        specular = glm::vec3(1.0f, 1.0f, 1.0f);

        constant = 1.0f;
        linear = 0.22f;
        quadratic = 0.2f;
    }

    DistantLight& enableShadowMap(int _resolution){
        shadowMapEnabled = true;
        textureRes = _resolution;
        }

    void createDepthBuffer();

    uint32_t getDepthTexture(){return depthTexture;}

    bool hasShadowMap(){return shadowMapEnabled;}
    void renderDepthMap(Scene& _scene, Camera& _cam);
};


#endif