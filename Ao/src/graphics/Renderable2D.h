#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Renderer2D;

struct VertexData
{
	glm::vec3 position;
	glm::vec2 uv;
	float sampler;
	unsigned int color;
};

class Renderable2D
{	
protected:
	Renderable2D();
public:
	Renderable2D(const glm::vec3& position, const glm::vec2& size, unsigned int color);
	Renderable2D(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	virtual ~Renderable2D() {}

	virtual void submit(Renderer2D* renderer) const;

	const glm::vec3& getPosition() const { return m_Position; }
	const glm::vec2& getSize() const { return m_Size; }
	const unsigned int getColor() const { return m_Color; }
	const std::vector<glm::vec2>& getUVs() const { return m_TexCoords; }
	const GLuint getTextureID() const { return m_TextureID; }
private:
	void setupDefaultUVs();
protected:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	unsigned int m_Color;
	std::vector<glm::vec2> m_TexCoords;
	GLuint m_TextureID;
};