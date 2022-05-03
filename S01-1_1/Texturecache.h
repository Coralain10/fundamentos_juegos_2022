#pragma once
#include <map>
#include <string>
#include "GLTexture.h"
class TextureCache
{
private:
	std::map<std::string, GLTexture> textureMap;
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(std::string texturePath);
};

