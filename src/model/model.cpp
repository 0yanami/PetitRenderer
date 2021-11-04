#include "model.hpp"

Model& Model::setScale(glm::vec3 _scale){
    scale = glm::mat4(1.0);
    scale = glm::scale(scale,_scale);
    return *this;
}

Model& Model::setRotation(float _angle, glm::vec3 _axis){
    rotation = glm::mat4(1.0);
    rotation = glm::rotate(rotation, glm::radians(_angle), _axis);
    return *this;
}

Model& Model::setPosition(glm::vec3 _pos){
    translate = glm::mat4{1.0};
    translate = glm::translate(translate, _pos);
    return *this;
}

Model& Model::setShaderType(SHADER_TYPE _shader){
    shaderType = _shader;
    return *this;
}

Model& Model::setTextures(std::string _diffusePath, std::string _specularPath, std::string _heightPath){
	diffuseMapPath = _diffusePath;
    specularMapPath = _specularPath;
    heightMapPath = _heightPath;
    shaderTessellation = true;
	return *this;
}

Model& Model::setTextures(std::string _diffusePath, std::string _specularPath){
	diffuseMapPath = _diffusePath;
    specularMapPath = _specularPath;
    shaderTessellation = false;
	return *this;
}