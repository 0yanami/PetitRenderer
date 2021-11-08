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

    //! Load the object on the gpu. This action is performed after opengl/glfw initialization
    virtual void load() = 0;

    //! Render the object on screen.
    virtual void render(std::vector<Light>& _lights,Camera& _cam) = 0;

    //! Set the scale the object in x,y,z axis.
    virtual Model& setScale(glm::vec3 _scale);

    //! Rotate the object around the given axis, angle is in degrees.
    virtual Model& setRotation(float _angle, glm::vec3 _axis);

    //! Set the position of the object in world space.
    virtual Model& setPosition(glm::vec3 _translate);

    //! Set textures for this model. Bump map is given so tesselation is enabled automatically.
    Model& setTextures(std::string _diffusePath, std::string _specularPath, std::string _heightPath);

    //! Set textures for this model. No bump map is given so tesselation is not enabled.
    Model& setTextures(std::string _diffusePath, std::string _specularPath);

    //! Enable tessellation for this model.
    Model& enableTesselation();

    //! Disable tessellation for this model.
    Model& disableTesselation();
};


//! a simple cube to test shader on
class Cube : public Model{
private:
    //! Load the right shader for the cube (phong,tessellation...)
    void loadShaders();

public:
    Cube(){};
    //! Create a cube of size _edgeSize.
    Cube(float _edgeSize);
    
    void load();
    void render(std::vector<Light>& _lights,Camera& _cam);
};



//! A model loaded from a file, it can contain multiple subModels inside it.
class FileModel : public Model{
private:
    
    std::vector<modelDescription> subModels;

    void loadShaders(modelDescription& model);
    void processMesh(aiMesh *_mesh, const aiScene *_scene, size_t _meshIdx);
public:
    FileModel(std::string _path, SMOOTH_NORMAL _smoothNormals);

    void load();
    void render(std::vector<Light>& _lights,Camera& _cam);

    FileModel& setScale(glm::vec3 _scale);
    FileModel& setRotation(float _angle, glm::vec3 _axis);
    FileModel& setPosition(glm::vec3 _translate);
    FileModel& subDivide(int _ite);
};



class CubeMap : public Cube{
private:
    int cubeMap;
    std::string cubeMapDir;
    std::string cubeMapExt;
    void loadShaders();
    
public:
    CubeMap(){};
    //! Directory of the images for the cubemap textures.
    /**
    * \param _directory The texture file names in the directory should be named :
    * - "right" (+x)
    * - "left" (-x)
    * - "top" (+y)
    * - "bottom" (-y)
    * - "back" (+z)
    * - "front" (-z)
    * \param _ext File format i.e png,jpg...
    **/
    CubeMap(std::string _directory, std::string _ext);

    //loadCubemapTexture(std::string _directory, std::string _ext)

    void load();
    void render(Camera& _cam);
};


class Sphere : public Model{

};

class Plane : public Model{

};

#endif