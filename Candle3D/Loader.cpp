#include "Loader.h"

#include <GL/glew.h>
#include <vector>
#include <fstream>


Loader::Loader()
{
}

Texture Loader::loadPNG(const std::string& filePath)
{
	Texture texture;

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width, height;

	if (loadFile(filePath, in) == false) {
		printf("Failed to load file to buffer");
	}

	printf("Loading texture...\n");

	int errorCode = decodePNG(out, width, height, in.data(), in.size());

	if (errorCode != 0) {
		printf("decodePNG failed with error: %s", std::to_string(errorCode));
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;
	texture.filePath = filePath;

	printf("Texture %s loaded\n", filePath.c_str());

	return texture;
}

bool Loader::loadFile(const std::string& fileName, std::vector<unsigned char>& buffer)
{
	//open file
	std::ifstream file(fileName, std::ios::binary);
	if (file.fail()) {
		printf("Failed to read in file: %s", fileName);
		return false;
	}

	//get size of file
	long size;
	file.seekg(0, std::ios::end);
	size = file.tellg();

	//reset to beginning
	file.seekg(0, std::ios::beg);

	//resize buffer
	size -= file.tellg();
	buffer.resize(size);

	//read file to buffer
	file.read((char*)&(buffer[0]), size);

	file.close();

	return true;
}

Loader::~Loader()
{
}
