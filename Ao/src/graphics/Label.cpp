#include "Label.h"
#include "Renderer2D.h"
#include "../managers/FontManager.h"
#include "../math/AoMath.h"

Label::Label(const std::string& text, float x, float y, unsigned int color)
{
	m_Text = text;
	m_Position = vec3(x, y, 0.0f);
	m_Color = color;
	m_Font = FontManager::get("default");
}

Label::Label(const std::string& text, float x, float y, Font* font, unsigned int color)
{
	m_Text = text;
	m_Position = vec3(x, y, 0.0f);
	m_Color = color;
	m_Font = font;
}

Label::Label(const std::string& text, float x, float y, const std::string& alias, unsigned int color)
{
	m_Text = text;
	m_Position = vec3(x, y, 0.0f);
	m_Color = color;
	m_Font = FontManager::get(alias);
}

Label::Label(const std::string& text, float x, float y, const std::string& alias, const vec4& color)
	: Renderable2D(vec3(x, y, 0.0f), vec2(0.0f, 0.0f), color)
{
	m_Text = text;
	m_Font = FontManager::get(alias);
}

Label::~Label()
{

}

void Label::submit(Renderer2D* renderer) const
{
	renderer->drawString(m_Text, m_Position, *m_Font, m_Color);
}