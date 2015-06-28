#include "Renderable2D.h"
#include "Renderer2D.h"

Renderable2D::Renderable2D()
{
	m_TextureID = 0;
	setupDefaultUVs();
}

Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, unsigned int color)
{
	m_Position = position;
	m_Size = size;
	m_Color = color;
	m_TextureID = 0;
	setupDefaultUVs();
}

Renderable2D::Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	m_Position = position;
	m_Size = size;
	m_TextureID = 0;
	setupDefaultUVs();

	int r = (int)(color.r * 255);
	int g = (int)(color.g * 255);
	int b = (int)(color.b * 255);
	int a = (int)(color.a * 255);
	
	m_Color = a << 24 | b << 16 | g << 8 | r;
}

void Renderable2D::submit(Renderer2D* renderer) const
{
	renderer->submit(this);
}

void Renderable2D::setupDefaultUVs()
{
	m_TexCoords.emplace_back(0, 1);
	m_TexCoords.emplace_back(1, 1);
	m_TexCoords.emplace_back(1, 0);
	m_TexCoords.emplace_back(0, 0);
}