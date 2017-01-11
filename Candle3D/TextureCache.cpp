#include "TextureCache.h"
#include "Loader.h"


TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

Texture TextureCache::loadTexture(const std::string & filePath)
{
	auto mit = _cache.find(filePath);

	if (mit == _cache.end()) {
		Texture tex = Loader::loadPNG(filePath);
		_cache.insert(std::make_pair(filePath, tex));
		return tex;
	}

	return mit->second;
}
