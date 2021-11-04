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

	indices = {
		0,1,2,
		3,4,5,
		
		6,7,8,
		9,10,11,

		12,13,14,
		15,16,17,

		18,19,20,
		21,22,23,

		24,25,26,
		27,28,29,

		30,31,32,
		33,34,35
	};

	translate = glm::mat4{1.0};
	scale     = glm::scale(glm::mat4{1.0},glm::vec3(_edgeSize));
	rotation  = glm::mat4{1.0};
}

//! Load vertex buffers and shader of cube
void Cube::load(){

    // gen geometry buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &nbo);
    glGenBuffers(1, &tbo);
	glGenBuffers(1, &ebo);
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

	//copy indices to ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);


    // Unbind the VAO
    glBindVertexArray(0);

	// load textures if defined
	if (diffuseMapPath != ""){
		diffuseMap = loadTexture(diffuseMapPath.c_str());
	}
	if (specularMapPath != ""){
		specularMap = loadTexture(specularMapPath.c_str());
	}
	if (heightMapPath != ""){
		heightMap = loadTexture(heightMapPath.c_str());
	}

	// load right shader
	if ((diffuseMapPath != "") && (specularMapPath != "")){
		if(shaderTessellation){
			std::cout << "init shader texture + tess"<< std::endl;
			shader = {"phongTexTess.vert", "phongTexTess.frag","phongTexTess.tesc","phongTexTess.tese"};
		} else {
			std::cout << "init shader texture"<< std::endl;
			shader = {"phongTex.vert", "phongTex.frag"};
		}
	} else {
		std::cout << "init shader basic"<< std::endl;
		shader = {"phong.vert", "phong.frag"};
	}
}


void Cube::render(std::vector<Light>& _lights,Camera& _cam)  {
	
    shader.use();
	glm::vec3 axis{0,1,0};
	rotation = glm::rotate(rotation,glm::radians(0.01f),axis);
    
    glm::mat4 model = translate*rotation*scale;

	shader.setMat4("model", model);
    shader.setMat4("view",_cam.getView());
    shader.setMat4("projection", _cam.getProj());


    // for specular highlight
    shader.setVec3("viewPos", _cam.getPos());
	
	shader.setFloat("material.specularStrength", 1.0f);

	//if textures are defined set uniform values
	if(diffuseMap != -1){
		shader.setInt("material.diffuse", 0);
	} else {
		shader.setVec3("material.diffuse", glm::vec3{1,0.2,0.2});
	}

	if(specularMap != -1){
		shader.setInt("material.specular", 1);
	} else {
		shader.setVec3("material.specular", glm::vec3{1,1,1});
	}

	if(heightMap != -1){
		shader.setInt("dispMap", 2);
		shader.setInt("tes_lod0", 64);
		shader.setInt("tes_lod1", 32);
		shader.setInt("tes_lod2", 16);
		shader.setFloat("dispStrength", 0.01);

	}

	shader.setFloat("material.shininess", 128.0f);
	


    for(uint32_t i = 0; i<_lights.size(); i++){
		shader.setBool("pointLights["+   std::to_string(i) + "].enabled",1);
        shader.setVec3("pointLights["+   std::to_string(i) + "].position",  _lights[i].getPos());
		
        shader.setVec3("pointLights[" +  std::to_string(i) + "].ambient",   _lights[i].getAmbiant());
	    shader.setVec3("pointLights[" +  std::to_string(i) + "].diffuse",   _lights[i].getDiffuse());
	    shader.setVec3("pointLights[" +  std::to_string(i) + "].specular",  _lights[i].getSpecular());

	    shader.setFloat("pointLights[" + std::to_string(i) + "].constant",  _lights[i].getConstant());
	    shader.setFloat("pointLights[" + std::to_string(i) + "].linear",    _lights[i].getLinear());
	    shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", _lights[i].getQuadratic());
    }
	if (_lights.size()<64){
		for (size_t i = _lights.size(); i<64; i++){
			shader.setBool("pointLights["+   std::to_string(i) + "].enabled",0);
		}
	}

    // bind diffuse texture
	glActiveTexture(GL_TEXTURE0);
	if (diffuseMap  != -1){
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// bind specular texture
	glActiveTexture(GL_TEXTURE1);
	if(specularMap  != -1){
		glBindTexture(GL_TEXTURE_2D, specularMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// bind height map texture
	glActiveTexture(GL_TEXTURE2);
	if(heightMap  != -1){
		glBindTexture(GL_TEXTURE_2D, heightMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

    glBindVertexArray(vao);

    
	if(heightMap  != -1){
		glDrawElements(GL_PATCHES , indices.size(), GL_UNSIGNED_INT, nullptr);
	} else {
		glDrawElements(GL_TRIANGLES , indices.size(), GL_UNSIGNED_INT, nullptr);
	}

}
