#include "model.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <fstream>



FileModel::FileModel(std::string _path, SMOOTH_NORMAL _smoothNormals){

	Assimp::Importer importer;
	
	const aiScene *scene = _smoothNormals?
		importer.ReadFile(_path, 
			  aiProcess_Triangulate 
			| aiProcess_FlipUVs
			| aiProcess_GenSmoothNormals):
		importer.ReadFile(_path, 
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
	}

	//center objects vertices
	double meanX = 0, meanY = 0, meanZ = 0;
	size_t count = 0;
	for(auto& subModel :subModels){
		for(size_t i = 0; i< subModel.vertices.size();i+=3){
			count++;
			meanX+=subModel.vertices[i];
			meanY+=subModel.vertices[i+1];
			meanZ+=subModel.vertices[i+2];
		}
	}
	meanX /= count;
	meanY /= count;
	meanZ /= count;
	for(auto& subModel :subModels){
		for(size_t i = 0; i<subModel.vertices.size();i+=3){
			count++;
			subModel.vertices[i] -= meanX;
			subModel.vertices[i+1] -= meanY;
			subModel.vertices[i+2] -= meanZ;
		}
	}

	//subtract min

}

//void FileModel::processMaterial(){
//
//}

void FileModel::processMesh(aiMesh *_mesh, const aiScene *_scene, size_t _meshIdx){
	auto& vert = subModels[_meshIdx].vertices;
	auto& ind = subModels[_meshIdx].indices;
	auto& norm = subModels[_meshIdx].normals;
	//auto& tex = subModels[_meshIdx].textureCoord;

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
	////if they exist add texture coordinates
	//if(_mesh->HasTextureCoords(0)){
	//	for(unsigned int i = 0; i < _mesh->mNumVertices; i++){
	//		tex.insert(tex.end(),
	//			{_mesh->mTextureCoords[0][i].x,_mesh->mTextureCoords[0][i].y});// TODO: add z if cubemap
    //	}
	//}

}

//! Load vertex buffers and shader of cube
void FileModel::load(){
	for(auto& subModel : subModels){

		// gen geometry buffers
    	glGenBuffers(1, &subModel.vbo);
    	glGenBuffers(1, &subModel.nbo);
    	glGenBuffers(1, &subModel.tbo);
		glGenBuffers(1, &subModel.ebo);
    	glGenVertexArrays(1, &subModel.vao);

		// Bind the vao
    	glBindVertexArray(subModel.vao);

		//copy indices to vbo
    	glBindBuffer(GL_ARRAY_BUFFER, subModel.vbo);
    	glBufferData(GL_ARRAY_BUFFER, subModel.vertices.size() * sizeof(GLfloat), subModel.vertices.data(), GL_STATIC_DRAW);
		// define array for vertices
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	glEnableVertexAttribArray(0);


    	// copy normals to nbo
    	glBindBuffer(GL_ARRAY_BUFFER, subModel.nbo);
    	glBufferData(GL_ARRAY_BUFFER, subModel.normals.size() * sizeof(GLfloat), subModel.normals.data(), GL_STATIC_DRAW);
    	// define array for normals
    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	glEnableVertexAttribArray(1);

		//// Copy texture coordinates array in element buffer
    	//glBindBuffer(GL_ARRAY_BUFFER, subModel.tbo);
    	//glBufferData(GL_ARRAY_BUFFER, subModel.textureCoord.size() * sizeof(GLfloat), subModel.textureCoord.data(), GL_STATIC_DRAW);
		//// define array for texture coordinates
    	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    	//glEnableVertexAttribArray(2);
		
		
		//copy indices to ebo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,subModel.ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, subModel.indices.size() * sizeof(GLfloat), subModel.indices.data(), GL_STATIC_DRAW);

    	// Unbind the VAO
    	glBindVertexArray(0);

		// load right shader

		if ((subModel.diffuseMapPath != "") ){
			subModel.diffuseMap = loadTexture(subModel.diffuseMapPath.c_str());
		}
		if(subModel.specularMapPath != ""){
			subModel.specularMap = loadTexture(subModel.specularMapPath.c_str());
		}
		if (subModel.heightMapPath != ""){
			subModel.heightMap = loadTexture(subModel.heightMapPath.c_str());
		}
		loadShaders(subModel);
	}
}


void FileModel::render(std::vector<Light*>& _lights,Camera& _cam)  {
	for(auto& subModel : subModels){

		auto& sh = subModel.shader;
    	sh.use();

		glm::vec3 axis{0,1,0};
		subModel.rotation = glm::rotate(subModel.rotation,glm::radians(0.03f),axis);
	
    	glm::mat4 model = subModel.translate*subModel.rotation*subModel.scale;

		sh.setMat4("model", model);
    	sh.setMat4("view",_cam.getView());
    	sh.setMat4("projection", _cam.getProj());


    	// for specular highlight
    	sh.setVec3("viewPos", _cam.getPos());

		sh.setFloat("material.specularStrength", 1.0f);

		//if textures are defined
		if(subModel.diffuseMap != -1){
			sh.setInt("material.diffuseTex", 0);
			sh.setBool("material.hasTexture",true);
		} else {
			sh.setVec3("material.diffuse", subModel.diffuseColor);
			sh.setBool("material.hasTexture",false);
		}

		if(subModel.specularMap != -1){
			sh.setInt("material.specularTex", 1);
		} else {
			sh.setVec3("material.specular", subModel.specularColor);
		}

		sh.setFloat("material.shininess", 128.0f);

		if(tessellation){
			//level of detail based on distance , adapts to any triangle size
			if(tqual == LOW){
				sh.setInt("tes_lod0", 16); //under 2 unit distance
				sh.setInt("tes_lod1", 4); //2 to 5 distance
				sh.setInt("tes_lod2", 2);  // farther than 5
			} else if (tqual == MEDIUM){
				sh.setInt("tes_lod0", 32); //under 2 unit distance
				sh.setInt("tes_lod1", 8); //2 to 5 distance
				sh.setInt("tes_lod2", 2);  // farther than 5
			} else if(tqual == HIGH){
				sh.setInt("tes_lod0", 64); //under 2 unit distance
				sh.setInt("tes_lod1", 16); //2 to 5 distance
				sh.setInt("tes_lod2", 4);  // farther than 5
			}
			
			// height map based tess
			if(m.heightMap != -1){
				sh.setInt("dispMap", 2);
				sh.setFloat("dispStrength", 0.01f);
			}
		}

		// point lights properties
		size_t maxLights = 10;
    	for(uint32_t i = 0; i<std::min(_lights.size(),maxLights); i++){

			sh.setBool("lights["+   std::to_string(i) + "].enabled",1);
			sh.setBool("lights["+   std::to_string(i) + "].hasShadowMap", _lights[i]->hasShadowMap());

    	    sh.setVec3("lights["+   std::to_string(i) + "].position",  _lights[i]->getPos());

    	    sh.setVec3("lights[" +  std::to_string(i) + "].ambient",   _lights[i]->getAmbiant());
		    sh.setVec3("lights[" +  std::to_string(i) + "].diffuse",   _lights[i]->getDiffuse());
		    sh.setVec3("lights[" +  std::to_string(i) + "].specular",  _lights[i]->getSpecular());

		    sh.setFloat("lights[" + std::to_string(i) + "].constant",  _lights[i]->getConstant());
		    sh.setFloat("lights[" + std::to_string(i) + "].linear",    _lights[i]->getLinear());
		    sh.setFloat("lights[" + std::to_string(i) + "].quadratic", _lights[i]->getQuadratic());
    	}
		if (_lights.size()<maxLights){
			for (size_t i = _lights.size(); i<maxLights; i++){
				sh.setBool("lights["+   std::to_string(i) + "].enabled",0);
			}
		}
		

    	// texture loading 

		glActiveTexture(GL_TEXTURE0);
		if (subModel.diffuseMap  != -1){
			glBindTexture(GL_TEXTURE_2D, subModel.diffuseMap);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glActiveTexture(GL_TEXTURE1);
		if(subModel.specularMap  != -1){
			glBindTexture(GL_TEXTURE_2D, subModel.specularMap);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// bind shadow maps textures
		int j = 0;
		for(int i = 0; i<_lights.size();i++){
			if(_lights[i]->hasShadowMap()){
				glActiveTexture(GL_TEXTURE3+j);
				DistantLight* li = dynamic_cast<DistantLight*>(_lights[i]);
				glBindTexture(GL_TEXTURE_2D, li->getDepthTexture());

				sh.setMat4("lightSpaceMatrix", li->getLightSpacematrix());
				sh.setInt("shadowMap", 3+j);
				j++;
			}
		}
		
    	glBindVertexArray(subModel.vao);
		//glDrawArrays(GL_TRIANGLES, 0, subModel.vertices.size()/3);
		if(tessellation){
			glDrawElements( GL_PATCHES, subModel.indices.size(), GL_UNSIGNED_INT, nullptr);
		} else {
			glDrawElements( GL_TRIANGLES, subModel.indices.size(), GL_UNSIGNED_INT, nullptr);
		}
    	
		glBindVertexArray(0);
	}
}

void FileModel::renderForDepth(Shader& _shader){
	for(auto& subModel : subModels){
	_shader.use();
	glm::mat4 model = subModel.translate*subModel.rotation*subModel.scale;

	_shader.setMat4("model", model);

	glBindVertexArray(subModel.vao);
	
	glDrawElements(GL_TRIANGLES , subModel.indices.size(), GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

FileModel& FileModel::setScale(float _scaleX, float _scaleY, float _scaleZ){
	for(auto& subModel : subModels){
    subModel.scale = glm::mat4(1.0);
    subModel.scale = glm::scale(subModel.scale,glm::vec3{_scaleX,_scaleY,_scaleZ});
	}
    return *this;
}

FileModel& FileModel::setScale(float _scale){
	for(auto& subModel : subModels){
    subModel.scale = glm::mat4(1.0);
    subModel.scale = glm::scale(subModel.scale,glm::vec3{_scale});
	}
    return *this;
}

FileModel& FileModel::setRotation(float _angle, float _axisX, float _axisY, float _axisZ){
	for(auto& subModel : subModels){
    subModel.rotation = glm::mat4(1.0);
    subModel.rotation = glm::rotate(subModel.rotation, glm::radians(_angle), 
							glm::vec3{_axisX,_axisY,_axisZ});
	}
    return *this;
}

FileModel& FileModel::setPosition(float _posX, float _posY, float _posZ){
	for(auto& subModel : subModels){
    subModel.translate = glm::mat4{1.0};
    subModel.translate = glm::translate(subModel.translate, glm::vec3{_posX,_posY,_posZ});
	}
    return *this;
}

void FileModel::loadShaders(modelDescription& model){
	// load right shader
	if(tessellation){
		model.shader = {"shaders/tessellation/phongPN.vert",
				 	"shaders/tessellation/phongPN.frag",
				 	"shaders/tessellation/phongPN.tesc",
				 	"shaders/tessellation/phongPN.tese"};
		
	} else {
		model.shader = {"shaders/phong.vert", "shaders/phong.frag"};
	}
	
}

FileModel& FileModel::setDiffuse(float _R,float _G,float _B){
	for(auto& subModel : subModels){
    subModel.diffuseColor = glm::vec3{_R,_G,_B};
	}
	return *this;
}

FileModel& FileModel::setSpecular(float _R,float _G,float _B){
	for(auto& subModel : subModels){
    subModel.specularColor = glm::vec3{_R,_G,_B};
	}
	return *this;
}


FileModel& FileModel::setDiffuse(float _C){
	for(auto& subModel : subModels){
    subModel.diffuseColor = glm::vec3{_C};
	}
	return *this;
}

FileModel& FileModel::setSpecular(float _C){
	for(auto& subModel : subModels){
    subModel.specularColor = glm::vec3{_C};
	}
	return *this;
}

FileModel& FileModel::enableTesselation(){
    tessellation = true;
    return *this;
}
FileModel& FileModel::disableTesselation(){
    tessellation = false;
    return *this;
}

FileModel& FileModel::enableTesselation(TESS_QUALITY _quality){
    tessellation = true;
	tqual = _quality;
    return *this;
}
FileModel& FileModel::disableTesselation(TESS_QUALITY _quality){
    tessellation = false;
	tqual = _quality;
    return *this;
}