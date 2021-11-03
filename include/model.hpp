#ifndef MODEL_H
#define MODEL_H

#include "headers.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "utils.hpp"

#include <vector>
#include <string>

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
    int diffuseMap = -1;
    int specularMap = -1;
    std::string diffuseMapPath = "";
    std::string specularMapPath = "";
    
    //la géométrie
    std::vector<GLfloat> vertices, normals, textureCoord;
    std::vector<GLuint>  indexes;

    // Model transformation
    glm::mat4 scale, rotation, translate;

public:
    Model(){};

    virtual void render(std::vector<Light>& _lights,Camera& _cam) = 0;

    Model& setScale(glm::vec3 _scale);
    Model& setRotation(float _angle, glm::vec3 _axis);
    Model& setPosition(glm::vec3 _translate);
    Model& setShader(Shader _shader);
    Model& setTex(std::string _diffusePath, std::string _specularPath);

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
};

class FileModel : public Model{
private:
    std::vector<int> diffuseMap = {-1};
    std::vector<int> specularMap = {-1};

    std::vector<std::string> diffuseMapPath = {""};
    std::vector<std::string> specularMapPath = {""};


    //la géométrie
    std::vector<std::vector<GLfloat>> vertices, normals, textureCoord;
    std::vector<std::vector<GLuint>>  indexes;

public:
    FileModel(){};
    FileModel(std::string _path);
    void load() override;
    void processMesh(aiMesh *mesh, const aiScene *scene);
    void render(std::vector<Light>& _lights,Camera& _cam) override;
};

class Sphere : public Model{

};

class Plane : public Model{

};

#endif