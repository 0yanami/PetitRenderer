#include "model.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <fstream>

FileModel::FileModel(std::string _path){


	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(_path, 
			  aiProcess_Triangulate 
			| aiProcess_FlipUVs
			| aiProcess_GenNormals);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

	//std::string directory = _path.substr(0, _path.find_last_of('/'));

	
	subModels.resize(scene->mNumMeshes);
	//process each mesh of the model

		std::cout << "processing "<< subModels.size()<< " submeshes from " 
		<<_path<< " ..." << std::endl;

	// configure each mesh
    for(size_t i = 0; i < scene->mNumMeshes; i++)
    {
		aiMesh *mesh = scene->mMeshes[i];

		subModels[i].translate = glm::mat4{1.0};
		subModels[i].scale     = glm::mat4{1.0};
		subModels[i].rotation  = glm::mat4{1.0};
        processMesh(mesh, scene,i);
		//processMaterial(mesh, scene);
    }
	// TODO: centrer l'origine à 0 (mean en x, y et z)

	
}

//void FileModel::processMaterial(){
//
//}

void FileModel::processMesh(aiMesh *_mesh, const aiScene *_scene, size_t _meshIdx){
	auto& vert = subModels[_meshIdx].vertices;
	auto& ind = subModels[_meshIdx].indices;
	auto& norm = subModels[_meshIdx].normals;

	// add vertices
	for(size_t i = 0; i < _mesh->mNumVertices; i++){
		vert.insert(vert.end(),
			{_mesh->mVertices[i].x,_mesh->mVertices[i].y,_mesh->mVertices[i].z});
    }
	// add normals
	for(size_t i = 0; i < _mesh->mNumVertices; i++){
		norm.insert(norm.end(),
			{_mesh->mNormals[i].x,_mesh->mNormals[i].y,_mesh->mNormals[i].z});
    }
	// add indices
	for(size_t i = 0; i < _mesh->mNumFaces; i++){
    	aiFace face = _mesh->mFaces[i];
    	for(size_t j = 0; j < face.mNumIndices; j++)
        ind.push_back(face.mIndices[j]);
	}

	//if they exist add texture coordinates
	//if(_mesh->HasTextureCoords(1)){
	//	for(unsigned int i = 0; i < _mesh->mNumVertices; i){
	//		tmpTexCoords.insert(tmpTexCoords.end(),
	//			{_mesh->mTextureCoords[i]->x,_mesh->mTextureCoords[i]->y});// TODO: add z if cubemap
    //	}
	//	textureCoord.push_back(tmpTexCoords);
	//	tmpTexCoords.clear();
	//}
}

//! Load vertex buffers and shader of cube
void FileModel::load(){
	for(auto& model : subModels){

		// gen geometry buffers
    	glGenBuffers(1, &model.vbo);
    	glGenBuffers(1, &model.nbo);
    	glGenBuffers(1, &model.tbo);
    	glGenVertexArrays(1, &model.vao);

		// Bind the vao
    	glBindVertexArray(model.vao);

    	// create and fill vertex data buffer
    	glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
    	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(GLfloat), model.vertices.data(), GL_STATIC_DRAW);
		// set vertex attribute pointer
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	glEnableVertexAttribArray(0);


    	// copy normals to nbo
    	glBindBuffer(GL_ARRAY_BUFFER, model.nbo);
    	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(GLfloat), model.normals.data(), GL_STATIC_DRAW);
    	// define array for normals
    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	glEnableVertexAttribArray(1);

    	//// Copy texture array in element buffer
    	//glBindBuffer(GL_ARRAY_BUFFER, tbo);
    	//glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);
		//// define array for texture
    	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	//glEnableVertexAttribArray(2);

    	// Unbind the VAO
    	glBindVertexArray(0);

		// load textures if defined
		if (model.diffuseMapPath != ""){
			model.diffuseMap = loadTexture(model.diffuseMapPath.c_str());
		}
		if (model.specularMapPath != ""){
			model.specularMap = loadTexture(model.specularMapPath.c_str());
		}
		// load right shader
		if ((model.diffuseMapPath != "") || (model.specularMapPath != "")){
			model.shader = {"cubeTex.vert", "cubeTex.frag"};
		} else {
			model.shader = {"cube.vert", "cube.frag"};
		}
	}
}


void FileModel::render(std::vector<Light>& _lights,Camera& _cam)  {
	for(auto& model : subModels){
		auto& sh = model.shader;
    	sh.use();
	
    	glm::mat4 mdl = model.translate*model.rotation*model.scale;

		sh.setMat4("model", mdl);
    	sh.setMat4("view",_cam.getView());
    	sh.setMat4("projection", _cam.getProj());


    	// for specular highlight
    	sh.setVec3("viewPos", _cam.getPos());

		sh.setFloat("material.specularStrength", 1.0f);

		//if textures are defined
		if(specularMap != -1){
			sh.setInt("material.specular", 1);
		} else {
			sh.setVec3("material.diffuse", glm::vec3{1,0.1,0.1});
		}
		if(diffuseMap != -1){
			sh.setInt("material.diffuse", 0);
		} else {
			sh.setVec3("material.specular", glm::vec3{1,1,1});
		}

		sh.setFloat("material.shininess", 128.0f);


    	for(uint32_t i = 0; i<_lights.size(); i++){
			sh.setBool("pointLights["+   std::to_string(i) + "].enabled",1);
    	    sh.setVec3("pointLights["+   std::to_string(i) + "].position",  _lights[i].getPos());

    	    sh.setVec3("pointLights[" +  std::to_string(i) + "].ambient",   _lights[i].getAmbiant());
		    sh.setVec3("pointLights[" +  std::to_string(i) + "].diffuse",   _lights[i].getDiffuse());
		    sh.setVec3("pointLights[" +  std::to_string(i) + "].specular",  _lights[i].getSpecular());

		    sh.setFloat("pointLights[" + std::to_string(i) + "].constant",  _lights[i].getConstant());
		    sh.setFloat("pointLights[" + std::to_string(i) + "].linear",    _lights[i].getLinear());
		    sh.setFloat("pointLights[" + std::to_string(i) + "].quadratic", _lights[i].getQuadratic());
    	}
		if (_lights.size()<64){
			for (size_t i = _lights.size(); i<64; i++){
				sh.setBool("pointLights["+   std::to_string(i) + "].enabled",0);
			}
		}

    	// mat4 scale, rotation, position, view
		glActiveTexture(GL_TEXTURE0);
		if (model.diffuseMap  != -1){
			glBindTexture(GL_TEXTURE_2D, model.diffuseMap);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glActiveTexture(GL_TEXTURE1);
		if(model.specularMap  != -1){
			glBindTexture(GL_TEXTURE_2D, model.specularMap);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

    	glBindVertexArray(model.vao);
    	glDrawArrays(GL_TRIANGLES, 0, model.vertices.size()/3);
	}
}



FileModel& FileModel::setScale(glm::vec3 _scale){
	std::cout << "called scale\n";
	for(auto& model : subModels){
    model.scale = glm::mat4(1.0);
    model.scale = glm::scale(model.scale,_scale);
	}
    return *this;
}

FileModel& FileModel::setRotation(float _angle, glm::vec3 _axis){
	std::cout << "called rotation\n";
	for(auto& model : subModels){
    model.rotation = glm::mat4(1.0);
    model.rotation = glm::rotate(model.rotation, glm::radians(_angle), _axis);
	}
    return *this;
}

FileModel& FileModel::setPosition(glm::vec3 _pos){
	std::cout << "called position\n";
	for(auto& model : subModels){
    model.translate = glm::mat4{1.0};
    model.translate = glm::translate(model.translate, _pos);
	}
    return *this;
}