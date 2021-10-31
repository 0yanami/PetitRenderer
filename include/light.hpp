#ifndef LIGHT_H
#define LIGHT_H

#include "headers.hpp"

class Light{
private:
    glm::vec3 position;

    glm::vec3 diffuse;
    glm::vec3 specular;

    //falloff parameters
    float ambiantStrength;
    float constant;
    float linear;
    float quadratic;

public:
    Light(glm::vec3 _position, glm::vec3 _color){
        position = _position;

        diffuse = _color;
        ambiantStrength = 0.25f;
        specular = glm::vec3(1.0f, 1.0f, 1.0f);

        constant = 1.0f;
        linear = 0.22f;
        quadratic = 0.2f;
    };

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
};


#endif