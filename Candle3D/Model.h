#pragma once

#include "Mesh.h"
#include "StaticShader.h"

#include <vector>
#include <string>
#include <assimp\scene.h>

class Model
{
public:
	Model();
	~Model();

	void init(const std::string&  path);
	void render(StaticShader& shader);

	std::vector<Mesh> getMeshes() { return _meshes; }

	glm::vec3 getAABBDimensions() const { return _aabbDims; }

private:
	std::vector<Mesh> _meshes;
	std::string _directory;

	float _maxX, _maxY, _maxZ, _minX, _minY, _minZ;
	glm::vec3 _aabbDims;

	void loadModel(const std::string&  path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

