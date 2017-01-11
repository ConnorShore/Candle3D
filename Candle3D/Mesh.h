#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "StaticShader.h"

#include <vector>
#include <GL\glew.h>

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	~Mesh();

	void render(StaticShader& shader);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	GLuint getVaoID() { return _vaoID; }

private:
	GLuint _vaoID, _vboID, _iboID;

	void setupMesh();
};

