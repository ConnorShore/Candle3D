#pragma once

#include "picoPNG.h"
#include "Texture.h"
#include <string>

class Loader
{
public:
	Loader();
	~Loader();

	static Texture loadPNG(const std::string& filePath);
	static bool loadFile(const std::string& fileName, std::vector<unsigned char>& buffer);

private:

};

