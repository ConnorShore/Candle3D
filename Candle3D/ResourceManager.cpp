#include "ResourceManager.h"

TextureCache ResourceManager::_texCache;

Texture ResourceManager::loadTexture(const std::string & filePath)
{
	return _texCache.loadTexture(filePath);
}
