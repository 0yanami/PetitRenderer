#include "model.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

Cube::Cube(float _edgeSize){
    vertices = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
    };

    normals = {
        0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,
	    1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f
    };
    
    textureCoord = {
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f
    };
	translate = glm::mat4{1.0};
	scale     = glm::mat4{1.0};
	rotation  = glm::mat4{1.0};
}

//! Load vertex buffers and shader of cube
void Cube::load(){

	shader = {"colors.vert", "colors.frag"};

    // gen geometry buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &nbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    // Bind the vao
    glBindVertexArray(vao);

    // copy vertices to vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);


    // create normals buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    // copy normals to nbo
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);


    // Copy our vertices array in a buffer for OpenGL to use
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(1);

    // Copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);
    
    // Unbind the VAO
    glBindVertexArray(0);

}


void Cube::render(std::vector<Light>& _lights,Camera& _cam)  {
	
    shader.use();
    
    glm::mat4 model = translate*rotation*scale;

	shader.setMat4("model", model);
    shader.setMat4("view",_cam.getView());
    shader.setMat4("projection", _cam.getProj());


    // for specular highlight
    shader.setVec3("viewPos", _cam.getPos());


    for(uint32_t i = 0; i<_lights.size(); i++){
        shader.setVec3("pointLights["+   std::to_string(i) + "].position",  _lights[i].getPos());
		
        shader.setVec3("pointLights[" +  std::to_string(i) + "].ambient",   _lights[i].getAmbiant());
	    shader.setVec3("pointLights[" +  std::to_string(i) + "].diffuse",   _lights[i].getDiffuse());
	    shader.setVec3("pointLights[" +  std::to_string(i) + "].specular",  _lights[i].getSpecular());

	    shader.setFloat("pointLights[" + std::to_string(i) + "].constant",  _lights[i].getConstant());
	    shader.setFloat("pointLights[" + std::to_string(i) + "].linear",    _lights[i].getLinear());
	    shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", _lights[i].getQuadratic());
    }

    // mat4 scale, rotation, position, view

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);

}


Cube& Cube::setScale(glm::vec3 _scale){
    scale = glm::mat4(1.0);
    scale = glm::scale(scale,_scale);
    return *this;
}

Cube& Cube::setRotation(float _angle, glm::vec3 _axis){
    rotation = glm::mat4(1.0);
    rotation = glm::rotate(rotation, glm::radians(_angle), _axis);
    return *this;
}

Cube& Cube::setPosition(glm::vec3 _pos){
    translate = glm::mat4{1.0};
    translate = glm::translate(translate, _pos);
    return *this;
}

Cube& Cube::setShader(Shader _shader){
    shader = _shader;
    return *this;
}

