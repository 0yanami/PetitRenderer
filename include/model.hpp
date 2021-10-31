#ifndef MODEL_H
#define MODEL_H

#include "headers.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "camera.hpp"

#include <vector>

class Model{
protected:
    // vbo = vertices
    // nbo = normals
    // ebo = indices
    // tbo = texture coord

    unsigned int vbo, nbo, ebo, tbo, vao;
    
    // le shader
    Shader shader;
    // les textures
    uint32_t diffuseMap, specularMap;
    
    //la géométrie
    std::vector<GLfloat> vertices, normals, textureCoord;
    std::vector<GLuint>  indexes;

    // Model transformation
    glm::mat4 scale, rotation, translate;

public:
    Model(){};

    virtual void render(std::vector<Light>& _lights,Camera& _cam) = 0;

    virtual Model& setScale(glm::vec3 _scale) = 0;
    virtual Model& setRotation(float _angle, glm::vec3 _axis) = 0;
    virtual Model& setPosition(glm::vec3 _translate) = 0;
    virtual Model& setShader(Shader _shader) = 0;

    virtual void load() = 0;
    
    //void subdivide();
    //void tesselation(bool activate);

};



class Cube : public Model{
public:
    Cube(){};
    Cube(float _edgeSize);
    void load() override;
    void render(std::vector<Light>& _lights,Camera& _cam) override;

    Cube& setScale(glm::vec3 _scale) override;
    Cube& setRotation(float _angle, glm::vec3 _axis) override;
    Cube& setPosition(glm::vec3 _translate) override;
    Cube& setShader(Shader _shader) override;
};

class Sphere : public Model{

};

class Plane : public Model{

};

#endif