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
    std::vector<GLuint>  indices;

    // Model transformation
    glm::mat4 scale, rotation, translate;

public:
    Model(){};

    virtual void load() = 0;
    virtual void render(std::vector<Light>& _lights,Camera& _cam) = 0;

    virtual Model& setScale(glm::vec3 _scale);
    virtual Model& setRotation(float _angle, glm::vec3 _axis);
    virtual Model& setPosition(glm::vec3 _translate);
    Model& setShader(Shader _shader);
    Model& setTex(std::string _diffusePath, std::string _specularPath);
    
    //void subdivide();
    //void tesselation(bool activate);

};



class Cube : public Model{
public:
    Cube(){};
    Cube(float _edgeSize);

    void load();
    void render(std::vector<Light>& _lights,Camera& _cam);
};


//! A model loaded from file, can contain multiple models inside it.
class FileModel : public Model{
private:

    struct subModel{
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
        std::vector<GLuint>  indices;

        // Model transformation
        glm::mat4 scale, rotation, translate;
    };

    std::vector<subModel> subModels;

public:
    FileModel(){};
    FileModel(std::string _path);

    void load();
    void processMesh(aiMesh *_mesh, const aiScene *_scene, size_t _meshIdx);
    void render(std::vector<Light>& _lights,Camera& _cam);

    FileModel& setScale(glm::vec3 _scale);
    FileModel& setRotation(float _angle, glm::vec3 _axis);
    FileModel& setPosition(glm::vec3 _translate);
};


class Sphere : public Model{

};

class Plane : public Model{

};

#endif