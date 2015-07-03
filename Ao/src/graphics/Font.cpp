#include "Font.h"

Font::Font(const std::string& filepath, float size)
{
	m_Atlas = ftgl::texture_atlas_new(512, 512, 2);
	m_Font = texture_font_new_from_file(m_Atlas, size, filepath.c_str());
	m_Size = size;
	m_Scale = vec2(1.0f, 1.0f);
}

Font::~Font()
{
	if (m_Font)
		texture_font_delete(m_Font);
	if (m_Atlas)
		texture_atlas_delete(m_Atlas);
}

void Font::setScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}