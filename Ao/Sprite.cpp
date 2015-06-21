#include "Sprite.h"
#include "Texture.h"
#include <iostream>

Sprite::Sprite(const glm::vec3& position)
	: Renderable2D(position, glm::vec2(50, 50), 0xffffffff)
{
	
}

Sprite::Sprite(const glm::vec3& position, const Texture* texture)
	: Renderable2D(position, glm::vec2(texture->width, texture->height), 0xffffffff)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const Texture* texture)
	: Renderable2D(position, size, 0xffffffff)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, unsigned int color, const Texture* texture)
	: Renderable2D(position, size, color)
{
	m_TextureID = texture->id;
}