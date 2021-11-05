#ifndef MODEL_H
#define MODEL_H

#include "headers.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "utils.hpp"

#include <vector>
#include <string>

enum SHADER_TYPE{
    PHONG
};

typedef enum {
    SMOOTH_NORMAL_ENABLE = true,
    SMOOTH_NORMAL_DISABLE = false
} SMOOTH_NORMAL;

class Model{
protected:
    //! une structure qui encapsule la description d'un modèle
    struct modelDescription{
            // vbo = vertices
        // nbo = normals
        // ebo = indices
        // tbo = texture coord
        unsigned int vbo, nbo, ebo, tbo, vao;

        // shading
        Shader shader;
        SHADER_TYPE shaderType = PHONG;

        std::string shaderVertPath = "";
        std::string shaderFragPath = "";
        std::string shaderTescPath = "";
        std::string shaderTesePath = "";

        int diffuseMap = -1;
        int specularMap = -1;
        int heightMap = -1;
        std::string diffuseMapPath = "";
        std::string specularMapPath = "";
        std::string heightMapPath = "";

        std::vector<GLfloat> vertices, normals, textureCoord;
        std::vector<GLuint>  indices;

        glm::mat4 scale, rotation, translate;
    };

    modelDescription m;
    //! tessellation enabled or disabled (disabled by default)
    bool tessellation = false;


public:
    Model(){};

    virtual void load() = 0;
    virtual void render(std::vector<Light>& _lights,Camera& _cam) = 0;

    virtual Model& setScale(glm::vec3 _scale);
    virtual Model& setRotation(float _angle, glm::vec3 _axis);
    virtual Model& setPosition(glm::vec3 _translate);
    Model& setShaderType(SHADER_TYPE _shader);
    Model& setTextures(std::string _diffusePath, std::string _specularPath, std::string _heightPath);
    Model& setTextures(std::string _diffusePath, std::string _specularPath);
    Model& enableTesselation();
    Model& disableTesselation();
    
    //void subdivide();
    //void tesselation(bool activate);

};



class Cube : public Model{
private:
    void loadShaders();
public:
    Cube(){};
    Cube(float _edgeSize);

    void load();
    void render(std::vector<Light>& _lights,Camera& _cam);
};



//! A model loaded from file, can contain multiple subModels inside it.
class FileModel : public Model{
private:
    
    std::vector<modelDescription> subModels;

    void loadShaders(modelDescription& model);

public:
    FileModel(){};
    FileModel(std::string _path, SMOOTH_NORMAL _smoothNormals);

    void load();
    void processMesh(aiMesh *_mesh, const aiScene *_scene, size_t _meshIdx);
    void render(std::vector<Light>& _lights,Camera& _cam);

    FileModel& setScale(glm::vec3 _scale);
    FileModel& setRotation(float _angle, glm::vec3 _axis);
    FileModel& setPosition(glm::vec3 _translate);
    FileModel& subDivide(int _ite);
};


class Sphere : public Model{

};

class Plane : public Model{

};

#endif