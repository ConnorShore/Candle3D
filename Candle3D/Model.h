#pragma once

#include "Mesh.h"
#include "StaticShader.h"

#include <vector>
#include <string>
#include <assimp\scene.h>

class Model
{
public:
	Model(const std::string&  path);
	~Model();

	void render(StaticShader& shader);

	std::vector<Mesh> getMeshes() { return _meshes; }

private:
	std::vector<Mesh> _meshes;
	std::string _directory;

	void loadModel(const std::string&  path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

