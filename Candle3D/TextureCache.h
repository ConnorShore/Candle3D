#pragma once

#include "Texture.h"

#include <map>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture loadTexture(const std::string& filePath);

private:
	std::map<std::string, Texture> _cache;
};

