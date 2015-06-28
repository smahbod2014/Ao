#include "Sprite.h"
#include "Texture.h"
#include <iostream>

Sprite::Sprite(const glm::vec3& position)
	: Renderable2D(position, glm::vec2(1, 1), 0xffffffff), position(m_Position)
{

}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	: Renderable2D(position, size, color), position(m_Position)
{

}

Sprite::Sprite(const glm::vec3& position, const Texture* texture)
	: Renderable2D(position, glm::vec2(texture->width, texture->height), 0xffffffff), position(m_Position)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, const Texture* texture)
	: Renderable2D(position, size, 0xffffffff), position(m_Position)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const glm::vec3& position, const glm::vec2& size, unsigned int color, const Texture* texture)
	: Renderable2D(position, size, color), position(m_Position)
{
	m_TextureID = texture->id;
}