#ifndef MODEL_H
#define MODEL_H

#define MAXLIGHTS 100

#include "headers.hpp"
#include "shader.hpp"
#include "light.hpp"
#include "ssao.hpp"
#include "camera.hpp"
#include "utils.hpp"


#include <vector>
#include <string>


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
        // The name of the object in the UI.
        std::string name;
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
        int metallicMap = -1;
        int heightMap = -1;
        int normalMap = -1;
        int AOMap = -1;

        std::string diffuseMapPath = "";
        std::string specularMapPath = "";
        std::string metallicMapPath = "";
        std::string heightMapPath = "";
        std::string normalMapPath = "";
        std::string AOMapPath = "";

        glm::vec3 diffuseColor = glm::vec3{0.9};
        glm::vec3 specularColor = glm::vec3{1.0};
        float metallic = 0.0f;
        float roughness = 0.0f;

        glm::vec2 texScaling = {1,1};

        std::vector<GLfloat> vertices, normals, textureCoord;
        std::vector<GLuint>  indices;

        float displacementStrength = 0.01f;

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
    Model& setTexDiffuse(std::string _path);
    Model& setTexSpecular(std::string _path);

    Model& setTexAlbedo(std::string _path);
    Model& setTexRoughness(std::string _path);
    Model& setTexMetallic(std::string _path);

    Model& setTexHeight( std::string _path);
    Model& setTexNormal( std::string _path);
    Model& setTexAO( std::string _path);

    Model& setTexScaling( glm::vec2 _scale);
    Model& setShaderType(SHADER_TYPE _type);

    //! Enable tessellation for this model default quality = medium
    Model& enableTesselation();
    //! Enable tessellation for this model with set \param _quality

    Model& enableTesselation(TESS_QUALITY _quality);
    //! Disable tessellation for this model.
    Model& disableTesselation();

    //! Set color of object (unused if textures are defined)
    Model& setDiffuse(glm::vec3 _color);
    Model& setSpecular(glm::vec3 _color);
    Model& setAlbedo(glm::vec3 _color);
    Model& setRoughness(float _roughness);
    Model& setMetallic(float _metallic);
    //! Set the displacement mutiplier factor to control displacement amount
    Model& displacementStrength(float _strength);

    std::string getName();
};


//! a simple cube to test shader on
class Cube : public Model{
    static int instance;
public:
    Cube(){};
    //! Create a cube of size _edgeSize.
    Cube(float _edgeSize);
};


//! A model loaded from a file, it can contain multiple subModels inside it.
class FileModel : public Model{
private:
    std::string name;
    static int instance;
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
    FileModel& setShaderType(SHADER_TYPE _type);
    FileModel& setRoughness(float _roughness);
    FileModel& setMetallic(float _metallic);
    FileModel& setAlbedo(glm::vec3 _color);
    std::string getName();
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
    static int instance;
    void inline pushIndices(int ind_1, int ind_2, int ind_3);
public:
    UVSphere(float _radius, int _nCols, int _nRows);
};

class Plane : public Model{
private:
    static int instance;
public: 
    Plane(glm::vec2 _size, int _ncol, int _nrows);
};

#endif