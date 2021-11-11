#include "model.hpp"

Model& Model::setScale(glm::vec3 _scale){
    m.scale = glm::mat4(1.0);
    m.scale = glm::scale(m.scale,_scale);
    return *this;
}

Model& Model::setRotation(float _angle, glm::vec3 _axis){
    m.rotation = glm::mat4(1.0);
    m.rotation = glm::rotate(m.rotation, glm::radians(_angle), _axis);
    return *this;
}

Model& Model::setPosition(glm::vec3 _pos){
    m.translate = glm::mat4{1.0};
    m.translate = glm::translate(m.translate, _pos);
    return *this;
}

Model& Model::setTextures(std::string _diffusePath, std::string _specularPath, std::string _heightPath){
	m.diffuseMapPath = _diffusePath;
    m.specularMapPath = _specularPath;
    m.heightMapPath = _heightPath;
    // heightmap given so enable tessellation
    tessellation = true;
	return *this;
}

Model& Model::setTextures(std::string _diffusePath, std::string _specularPath){
	m.diffuseMapPath = _diffusePath;
    m.specularMapPath = _specularPath;
	return *this;
}

Model& Model::enableTesselation(){
    tessellation = true;
    return *this;
}
Model& Model::disableTesselation(){
    tessellation = false;
    return *this;
}

Model& Model::setDiffuse(glm::vec3 _color){
	m.diffuseColor = _color;
	return *this;
}