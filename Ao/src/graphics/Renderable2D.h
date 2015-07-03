#pragma once

#include <GL/glew.h>
#include <vector>
#include "../math/AoMath.h"

class Renderer2D;

struct VertexData
{
	vec3 position;
	vec2 uv;
	float sampler;
	unsigned int color;
};

class Renderable2D
{	
protected:
	Renderable2D();
public:
	Renderable2D(const vec3& position, const vec2& size, unsigned int color);
	Renderable2D(const vec3& position, const vec2& size, const vec4& color);
	virtual ~Renderable2D() {}

	virtual void submit(Renderer2D* renderer) const;

	const vec3& getPosition() const { return m_Position; }
	const vec2& getSize() const { return m_Size; }
	const unsigned int getColor() const { return m_Color; }
	const std::vector<vec2>& getUVs() const { return m_TexCoords; }
	const GLuint getTextureID() const { return m_TextureID; }
private:
	void setupDefaultUVs();
protected:
	vec3 m_Position;
	vec2 m_Size;
	unsigned int m_Color;
	std::vector<vec2> m_TexCoords;
	GLuint m_TextureID;
};