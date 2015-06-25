#pragma once

#include <GL/glew.h>
#include <vector>
#include <freetype-gl.h>

#include "Renderer2D.h"
#include "Renderable2D.h"

#define MAX_SPRITES 60000
#define MAX_TEXTURES 32
#define BUFFER_SIZE sizeof(VertexData) * 4 * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * 6

#define VERTEX_INDEX 0
#define UV_INDEX 1
#define SAMPLER_INDEX 2
#define COLOR_INDEX 3

class BatchRenderer2D : public Renderer2D
{
public:
	BatchRenderer2D();
	virtual ~BatchRenderer2D();

	virtual void begin() override;
	virtual void submit(const Renderable2D* renderable) override;
	virtual void drawString(const std::string& text, const glm::vec3& position, unsigned int color) override;
	virtual void end() override;
	virtual void flush() override;
private:
	void init();

	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_Ibo;
	GLsizei m_IndexCount;
	VertexData* m_Buffer = nullptr;
	ftgl::texture_atlas_t* m_Atlas;
	ftgl::texture_font_t* m_Font;

	std::vector<GLuint> m_Textures;
};