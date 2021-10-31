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
	scale     = glm::scale(glm::mat4{1.0},glm::vec3(_edgeSize));
	rotation  = glm::mat4{1.0};
}

//! Load vertex buffers and shader of cube
void Cube::load(){



	shader = {"colors.vert", "colors.frag"};

    // gen geometry buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &nbo);
    glGenBuffers(1, &tbo);
    glGenVertexArrays(1, &vao);

	// Bind the vao
    glBindVertexArray(vao);

    // create and fill vertex data buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	// set vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);


    // copy normals to nbo
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    // define array for normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(1);

    // Copy texture array in element buffer
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);
	// define array for texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(2);

    // Unbind the VAO
    glBindVertexArray(0);

	// load textures if defined
	if (diffuseMapPath != ""){
		diffuseMap = loadTexture(diffuseMapPath.c_str());
	}
	if (specularMapPath != ""){
		specularMap = loadTexture(specularMapPath.c_str());
	}

}


void Cube::render(std::vector<Light>& _lights,Camera& _cam)  {
	
    shader.use();
    
    glm::mat4 model = translate*rotation*scale;

	shader.setMat4("model", model);
    shader.setMat4("view",_cam.getView());
    shader.setMat4("projection", _cam.getProj());


    // for specular highlight
    shader.setVec3("viewPos", _cam.getPos());
	
	shader.setFloat("material.specularStrength", 2.0f);
	//if textures are defined
	if(specularMap != -1){
		shader.setInt("material.specular", 1);
	}
	if(diffuseMap != -1){
		shader.setInt("material.diffuse", 0);
	} else {
		shader.setVec3("material.diffuse", glm::vec3{1,0,0});
	}
	

	shader.setFloat("material.shininess", 128.0f);


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
	if (diffuseMap  != -1){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
	}
	if(specularMap  != -1){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
	}

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

Cube& Cube::setTexDiffuse(std::string _path){
	diffuseMapPath = _path;
	return *this;
}
Cube& Cube::setTexSpecular(std::string _path){
	specularMapPath = _path;
	return *this;
}
