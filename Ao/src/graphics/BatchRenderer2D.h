#pragma once

#include <GL/glew.h>
#include <vector>
#include <freetype-gl.h>

#include "Renderer2D.h"
#include "Renderable2D.h"

#define MAX_SPRITES 60000
#ifdef AO_EMSCRIPTEN
	#define MAX_TEXTURES 8
#else
	#define MAX_TEXTURES 32
#endif
#define BUFFER_SIZE sizeof(VertexData) * 4 * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * 6

#define VERTEX_INDEX 0
#define UV_INDEX 1
#define SAMPLER_INDEX 2
#define COLOR_INDEX 3

class vec3;

class BatchRenderer2D : public Renderer2D
{
public:
	BatchRenderer2D();
	virtual ~BatchRenderer2D();

	virtual void begin() override;
	virtual void submit(const Renderable2D* renderable) override;
	virtual void drawString(const std::string& text, const vec3& position, const Font& font, unsigned int color) override;
	virtual void end() override;
	virtual void flush() override;
private:
	void init();

	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_Ibo;
	GLsizei m_IndexCount;
	VertexData* m_Buffer = nullptr;
#ifdef AO_EMSCRIPTEN
	VertexData* m_BufferBase = nullptr;
#endif

	std::vector<GLuint> m_Textures;
};