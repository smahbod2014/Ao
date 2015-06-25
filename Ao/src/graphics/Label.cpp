#include "Label.h"
#include "Renderer2D.h"

Label::Label(const std::string& text, float x, float y, unsigned int color)
{
	m_Text = text;
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = 0.0f;
	m_Color = color;
}

Label::~Label()
{

}

void Label::submit(Renderer2D* renderer) const
{
	renderer->drawString(m_Text, m_Position, m_Color);
}