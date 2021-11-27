#include "model.hpp"

Model& Model::setScale(glm::vec3 _scale){
    m.scale = glm::mat4(1.0);
    m.scale = glm::scale(m.scale,_scale);
    return *this;
}

Model& Model::setRotation(float _angle, glm::vec3 _axis){
    m.rotation = glm::mat4(1.0);
    m.rotation = glm::rotate(m.rotation, glm::radians(_angle),_axis);
    return *this;
}

Model& Model::setPosition(glm::vec3 _pos){
    m.translate = glm::mat4{1.0};
    m.translate = glm::translate(m.translate, _pos);
    return *this;
}

Model& Model::setTexDiffuse(std::string _diffusePath){
    m.diffuseMapPath = _diffusePath;
    return *this;
}

Model& Model::setTexSpecular(std::string _specularPath){
    m.specularMapPath = _specularPath;
    return *this;
}

Model& Model::setTexHeight( std::string _heightPath){
    m.heightMapPath = _heightPath;
    tessellation = true;
    return *this;
}

Model& Model::setTexNormal( std::string _normalPath){
    m.normalMapPath = _normalPath;
    return *this;
}

Model& Model::setTexAO( std::string _AOPath){
    m.AOMapPath = _AOPath;
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

Model& Model::setSpecular(glm::vec3 _color){
	m.specularColor = _color;
	return *this;
}

Model& Model::displacementStrength(float _strength){
    m.displacementStrength = _strength;
    return *this;
}