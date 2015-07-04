#include "Layer.h"
#include "Renderer2D.h"
#include "Renderable2D.h"
#include "BatchRenderer2D.h"
#include "Shader.h"

Layer::Layer(Renderer2D* renderer, Shader* shader, const mat4& projection)
{
	m_Renderer = renderer;
	m_Shader = shader;
	m_Projection = projection;

	shader->bind();
	shader->setUniformMatrix4("projMatrix", projection);
	for (int i = 0; i < MAX_TEXTURES; i++)
#ifdef AO_EMSCRIPTEN
		shader->setUniform1("texture_" + std::to_string(i), i);
#else
		shader->setUniform1("textures[" + std::to_string(i) + "]", i);
#endif
	shader->unbind();
}

Layer::~Layer()
{
	if (m_Renderer) delete m_Renderer;
	if (m_Shader) delete m_Shader;
	for (size_t i = 0; i < m_Renderables.size(); i++)
		delete m_Renderables[i];

	m_Renderables.clear();
}

void Layer::add(Renderable2D* renderable)
{
	m_Renderables.push_back(renderable);
}

void Layer::render()
{
	m_Shader->bind();
	m_Renderer->begin();
	
	for (size_t i = 0; i < m_Renderables.size(); i++)
		m_Renderables[i]->submit(m_Renderer);

	m_Renderer->end();
	m_Shader->unbind();
}