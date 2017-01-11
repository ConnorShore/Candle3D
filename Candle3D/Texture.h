#pragma once

#include <string>
#include <GL\glew.h>
#include <assimp\IOStream.hpp>

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};