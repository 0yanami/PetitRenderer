#ifndef MODEL_H
#define MODEL_H

#include "headers.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "ssao.hpp"
#include "camera.hpp"
#include "utils.hpp"


#include <vector>
#include <string>

enum SHADER_TYPE{
    PHONG
};

enum TESS_QUALITY{
    LOW,
    MEDIUM,
    HIGH
};

typedef enum {
    SMOOTH_NORMAL_ENABLE = true,
    SMOOTH_NORMAL_DISABLE = false
} SMOOTH_NORMAL;

class Scene;

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
        int normalMap = -1;
        int AOMap = -1;

        std::string diffuseMapPath = "";
        std::string specularMapPath = "";
        std::string heightMapPath = "";
        std::string normalMapPath = "";
        std::string AOMapPath = "";

        glm::vec3 diffuseColor = glm::vec3{0.9};
        glm::vec3 specularColor = glm::vec3{1.0};

        glm::vec2 texScaling = {1,1};

        std::vector<GLfloat> vertices, normals, textureCoord;
        std::vector<GLuint>  indices;

        float displacementStrength = 0.01;

        glm::mat4 scale, rotation, translate;

        TESS_QUALITY tqual = MEDIUM;
        bool tessellation = false;
    };

    modelDescription m;
    //! tessellation enabled or disabled (disabled by default)
    

    void loadShaders();
public:
    Model(){};

    //! Load the object on the gpu. This action is performed after opengl/glfw initialization
    virtual void load();

    //! Render the object on screen.
    virtual void render(Scene* _scene);
    
    //! render objects faster for shadow map
    /**
     * \param _shader the depth map shader.
     **/
    virtual void renderForDepth(Shader& _shader);

    //! Set the scale the object in x,y,z axis.
    virtual Model& setScale(glm::vec3 _scale);

    //! Rotate the object around the given axis, angle is in degrees.
    virtual Model& setRotation(float _angle, glm::vec3 _axis);

    //! Set the position of the object in world space.
    virtual Model& setPosition(glm::vec3 _pos);

    //! Set textures for this model. When bump map is given, tesselation is enabled automatically.
    Model& setTexDiffuse(std::string _diffusePath);
    Model& setTexSpecular(std::string _specularPath);
    Model& setTexHeight( std::string _heightPath);
    Model& setTexNormal( std::string _NormalPath);
    Model& setTexAO( std::string _AOPath);
    Model& setTexScaling( glm::vec2 _scale);

    //! Enable tessellation for this model default quality = medium
    Model& enableTesselation();
    //! Enable tessellation for this model with set \param _quality

    Model& enableTesselation(TESS_QUALITY _quality);
    //! Disable tessellation for this model.
    Model& disableTesselation();

    //! Set diffuse color of object (unused if textures are defined)
    Model& setDiffuse(glm::vec3 _color);

    //! Set specular color of object
    Model& setSpecular(glm::vec3 _color);
    //! Set the displacement mutiplier factor to control displacement amount
    Model& displacementStrength(float _strength);
};


//! a simple cube to test shader on
class Cube : public Model{
public:
    Cube(){};
    //! Create a cube of size _edgeSize.
    Cube(float _edgeSize);
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
    void render(Scene* _scene);
    void renderForDepth(Shader& _shader); 

    FileModel& setScale(glm::vec3 _scale);
    FileModel& setRotation(float _angle, glm::vec3 _axis);
    FileModel& setPosition(glm::vec3 _pos);
    FileModel& setDiffuse(glm::vec3 _color);
    FileModel& setSpecular(glm::vec3 _color);
    FileModel& enableTesselation();
    FileModel& disableTesselation();
    FileModel& enableTesselation(TESS_QUALITY _quality);
    FileModel& displacementStrength(float _strength);
    FileModel& setTexScaling(glm::vec2 _scale);
};



class CubeMap : public Cube{
private:
    int cubeMap;
    std::string cubeMapDir;
    void loadShaders();
    
public:
    CubeMap(){};
    /**
    *  Create a Cubemap to be added to a scene.
    *  File extensions are found automatically (png,jpg,jpeg are supported).
    * \param _directory The texture files directory
    **/
    CubeMap(std::string _directory);

    void load();
    void render(Scene* _scene);
};


class UVSphere : public Model{
private:
    void inline pushIndices(int ind_1, int ind_2, int ind_3);
public:
    UVSphere(float _radius, int _nCols, int _nRows);
};

class Plane : public Model{
public: 
    Plane(glm::vec2 _size, int _ncol, int _nrows);
};

#endif