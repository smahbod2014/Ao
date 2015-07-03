#include "Sprite.h"
#include "Texture.h"
#include "../math/AoMath.h"

Sprite::Sprite(const vec3& position)
	: Renderable2D(position, vec2(1.0f, 1.0f), 0xffffffff), position(m_Position)
{

}

Sprite::Sprite(const vec3& position, const vec2& size, const vec4& color)
	: Renderable2D(position, size, color), position(m_Position)
{

}

Sprite::Sprite(const vec3& position, const Texture* texture)
	: Renderable2D(position, vec2(1.0f, 1.0f), 0xffffffff), position(m_Position)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const vec3& position, const vec2& size, const Texture* texture)
	: Renderable2D(position, size, 0xffffffff), position(m_Position)
{
	m_TextureID = texture->id;
}

Sprite::Sprite(const vec3& position, const vec2& size, unsigned int color, const Texture* texture)
	: Renderable2D(position, size, color), position(m_Position)
{
	m_TextureID = texture->id;
}