#include "model.hpp"

Model& Model::setScale(float _scaleX, float _scaleY, float _scaleZ){
    m.scale = glm::mat4(1.0);
    m.scale = glm::scale(m.scale,glm::vec3{_scaleX,_scaleY,_scaleZ});
    return *this;
}

Model& Model::setScale(float _scale){
    m.scale = glm::mat4(1.0);
    m.scale = glm::scale(m.scale,glm::vec3{_scale});
    return *this;
}

Model& Model::setRotation(float _angle, float _axisX, float _axisY, float _axisZ){
    m.rotation = glm::mat4(1.0);
    m.rotation = glm::rotate(m.rotation, glm::radians(_angle), 
                    glm::vec3{_axisX,_axisY,_axisZ});
    return *this;
}

Model& Model::setPosition(float _posX, float _posY, float _posZ){
    m.translate = glm::mat4{1.0};
    m.translate = glm::translate(m.translate, glm::vec3{_posX,_posY,_posZ});
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

Model& Model::setDiffuse(float _R,float _G,float _B){
	m.diffuseColor = glm::vec3{_R,_G,_B};
	return *this;
}

Model& Model::setSpecular(float _R,float _G,float _B){
	m.specularColor = glm::vec3{_R,_G,_B};
	return *this;
}

Model& Model::setDiffuse(float _C){
	m.diffuseColor = glm::vec3{_C};
	return *this;
}

Model& Model::setSpecular(float _C){
	m.specularColor = glm::vec3{_C};
	return *this;
}