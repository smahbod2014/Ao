#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include "../graphics/Texture.h"

class TextureManager
{
public:
	static void loadTexture(const std::string& alias, const std::string& path);
	static const Texture* getTexture(const std::string& alias);
private:
	static std::map<const std::string, const Texture*> m_Cache;
};