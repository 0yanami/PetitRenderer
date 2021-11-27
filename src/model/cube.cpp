#include "model.hpp"
#include "scene.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <algorithm>


Cube::Cube(float _edgeSize){

	m.vertices = {
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

    m.normals = {
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
    
    m.textureCoord = {
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

	m.indices = {
		0,2,1,
		3,5,4,
		
		6,7,8,
		9,10,11,

		12,13,14,
		15,16,17,

		18,20,19,
		21,23,22,

		24,25,26,
		27,28,29,

		30,32,31,
		33,35,34
	};
    

	m.translate = glm::mat4{1.0};
	m.scale     = glm::scale(glm::mat4{1.0},glm::vec3(_edgeSize));
	m.rotation  = glm::mat4{1.0};
}


void Cube::load(){

    // gen geometry buffers
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.nbo);
    glGenBuffers(1, &m.tbo);
	glGenBuffers(1, &m.ebo);
    glGenVertexArrays(1, &m.vao);

	// Bind the vao
    glBindVertexArray(m.vao);

    // create and fill vertex data buffer
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(GLfloat), m.vertices.data(), GL_STATIC_DRAW);
	// set vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(0);


    // copy normals to nbo
    glBindBuffer(GL_ARRAY_BUFFER, m.nbo);
    glBufferData(GL_ARRAY_BUFFER, m.normals.size() * sizeof(GLfloat), m.normals.data(), GL_STATIC_DRAW);
    // define array for normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(1);

    // Copy texture array in element buffer
    glBindBuffer(GL_ARRAY_BUFFER, m.tbo);
    glBufferData(GL_ARRAY_BUFFER, m.textureCoord.size() * sizeof(GLfloat), m.textureCoord.data(), GL_STATIC_DRAW);
	// define array for texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glEnableVertexAttribArray(2);

	//copy indices to ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.indices.size() * sizeof(GLfloat), m.indices.data(), GL_STATIC_DRAW);


    // Unbind the VAO
    glBindVertexArray(0);

	// load textures if defined
	if (m.diffuseMapPath != ""){
		m.diffuseMap = loadTexture(m.diffuseMapPath.c_str());
	}
	if (m.specularMapPath != ""){
		m.specularMap = loadTexture(m.specularMapPath.c_str());
	}
	if (m.heightMapPath != ""){
		m.heightMap = loadTexture(m.heightMapPath.c_str());
	}

	loadShaders();
}


void Cube::render(Scene* _scene)  {
	Camera& cam = _scene->getCam();
	SSAO* ssao =  _scene->getSSAO();
	std::vector<Light*>& lights =  _scene->getLights();

    m.shader.use();
	
    glm::mat4 model = m.translate*m.rotation*m.scale;

	m.shader.setMat4("model", model);
    m.shader.setMat4("view", cam.getView());
    m.shader.setMat4("projection", cam.getProj());
	m.shader.setVec2("screenSize", glm::vec2(cam.getResWidth(),cam.getResHeight()));
    m.shader.setVec3("viewPos", cam.getPos());
	m.shader.setFloat("exposure",_scene->getExposure());
	

	m.shader.setFloat("material.specularStrength", 0.5f);

	//if textures are defined set uniform values
	if(m.diffuseMap != -1){
		m.shader.setInt("material.diffuseTex", 0);
		m.shader.setBool("material.hasTexture",true);
	} else {
		m.shader.setVec3("material.diffuse", m.diffuseColor);
		m.shader.setBool("material.hasTexture",false);
	}

	if(m.specularMap != -1){
		m.shader.setInt("material.specularTex", 1);
	} else {
		m.shader.setVec3("material.specular", m.specularColor);
	}
	m.shader.setFloat("material.shininess", 64.0f);

	if(m.heightMap != -1){
		m.shader.setInt("dispMap", 2);
		m.shader.setInt("tes_lod0", 64);
		m.shader.setInt("tes_lod1", 32);
		m.shader.setInt("tes_lod2", 4);
		m.shader.setFloat("dispStrength", m.displacementStrength);
	}

	// bind diffuse texture
	glActiveTexture(GL_TEXTURE0);
	if (m.diffuseMap  != -1){
		glBindTexture(GL_TEXTURE_2D, m.diffuseMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// bind specular texture
	glActiveTexture(GL_TEXTURE1);
	if(m.specularMap  != -1){
		glBindTexture(GL_TEXTURE_2D, m.specularMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// bind height map texture
	glActiveTexture(GL_TEXTURE2);
	if(m.heightMap  != -1){
		glBindTexture(GL_TEXTURE_2D, m.heightMap);
	} else {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// bind SSAO texture if enabled
	if (ssao != nullptr){
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, ssao->getSSAOBlurTexture());
		m.shader.setInt("SSAOTexture", 3);
		m.shader.setBool("SSAOenabled", true);
	} else {
		m.shader.setBool("SSAOenabled", false);
	}


	
	size_t maxLights = 10;
	int j = 0;
    for(uint32_t i = 0; i<std::min(lights.size(),maxLights); i++){
		if(lights[i]->hasShadowMap()){
			glActiveTexture(GL_TEXTURE4+j);
			DistantLight* li = dynamic_cast<DistantLight*>(lights[i]);
			glBindTexture(GL_TEXTURE_2D, li->getDepthTexture());

			m.shader.setMat4("lightSpaceMatrix["+std::to_string(j)+"]", li->getLightSpacematrix());
			m.shader.setInt("shadowMap["+std::to_string(j)+"]", 4+j);
			m.shader.setInt("lights["+   std::to_string(i) + "].shadowMapId", j);
			j++;
		} else {
			m.shader.setInt("lights["+   std::to_string(i) + "].shadowMapId", -1);
		}

		m.shader.setBool("lights["+   std::to_string(i) + "].enabled",1);

        m.shader.setVec3("lights["+   std::to_string(i) + "].position",  lights[i]->getPos());

        m.shader.setVec3("lights[" +  std::to_string(i) + "].ambient",   lights[i]->getAmbiant());
	    m.shader.setVec3("lights[" +  std::to_string(i) + "].diffuse",   lights[i]->getDiffuse());
	    m.shader.setVec3("lights[" +  std::to_string(i) + "].specular",  lights[i]->getSpecular());

	    m.shader.setFloat("lights[" + std::to_string(i) + "].constant",  lights[i]->getConstant());
	    m.shader.setFloat("lights[" + std::to_string(i) + "].linear",    lights[i]->getLinear());
	    m.shader.setFloat("lights[" + std::to_string(i) + "].quadratic", lights[i]->getQuadratic());
    }
	if (lights.size()<maxLights){
		for (size_t i = lights.size(); i<maxLights; i++){
			m.shader.setBool("lights["+   std::to_string(i) + "].enabled",0);
		}
	}


    glBindVertexArray(m.vao);
    
	if(tessellation){
		glDrawElements(GL_PATCHES , m.indices.size(), GL_UNSIGNED_INT, nullptr);
	} else {
		glDrawElements(GL_TRIANGLES , m.indices.size(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);

}

void Cube::renderForDepth(Shader& _shader){

	_shader.use();
	glm::mat4 model = m.translate*m.rotation*m.scale;

	_shader.setMat4("model", model);

	glBindVertexArray(m.vao);
	
	glDrawElements(GL_TRIANGLES , m.indices.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

void Cube::loadShaders(){
	// load right shader
	if(tessellation){
		if (m.heightMapPath != ""){
			std::cout << "using phong bump shader\n";
			m.shader = {"shaders/tessellation/phong.vert",
				 "shaders/phong.frag",
				 "shaders/tessellation/phongBump.tesc",
				 "shaders/tessellation/phongBump.tese"};
		} else {
			m.shader = {"shaders/tessellation/phong.vert",
				 "shaders/phong.frag",
				 "shaders/tessellation/phongPN.tesc",
				 "shaders/tessellation/phongPN.tese"};
		}
		
	} else {
		m.shader = {"shaders/phong.vert", "shaders/phong.frag"};
	}
}

