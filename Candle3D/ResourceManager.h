#pragma once

#include <string>

#include "TextureCache.h"
#include "Texture.h"

class ResourceManager
{
public:

	static Texture loadTexture(const std::string& filePath);

private:
	static TextureCache _texCache;
};

