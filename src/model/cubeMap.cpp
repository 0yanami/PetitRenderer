#include "model.hpp"

CubeMap::CubeMap(std::string _directory, std::string _ext){
    m.vertices = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f 
    };
    cubeMapDir = _directory;
    cubeMapExt = _ext;
}

void CubeMap::load(){

    glGenBuffers(1, &m.vbo);
    glGenVertexArrays(1, &m.vao);

    glBindVertexArray(m.vao);

    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(GLfloat), m.vertices.data(), GL_STATIC_DRAW);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);

    cubeMap = loadCubeMapTexture(cubeMapDir,cubeMapExt);

    loadShaders();
    
    glBindVertexArray(0);

    
}

void CubeMap::render(Camera& _cam){

    glDepthMask(GL_FALSE);

    m.shader.use();

    m.shader.setMat4("view", glm::mat4(glm::mat3(_cam.getView())));
    //m.shader.setMat4("view",_cam.getView());
    m.shader.setMat4("projection", _cam.getProj());
    m.shader.setInt("skybox",0);
    
    glBindVertexArray(m.vao);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    glDepthMask(GL_TRUE);

}

void CubeMap::loadShaders(){
    m.shader = {"shaders/cubemap.vert","shaders/cubemap.frag"};
}