#pragma once

#include <string>
#include <freetype-gl.h>
#include <glm/glm.hpp>

class Font
{
public:
	Font(const std::string& filepath, float size);
	~Font();

	void setScale(float x, float y);

	inline const unsigned int getID() const { return m_Atlas->id; }
	inline ftgl::texture_font_t* getFont() const { return m_Font; }
	inline const float getSize() const { return m_Size; }
	inline const glm::vec2& getScale() const { return m_Scale; }
private:
	ftgl::texture_atlas_t* m_Atlas;
	ftgl::texture_font_t* m_Font;
	float m_Size;
	glm::vec2 m_Scale;
};