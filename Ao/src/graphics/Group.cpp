#include "Group.h"
#include "Renderer2D.h"

Group::Group(const glm::mat4& matrix)
{
	m_Transformation = matrix;
}

Group::~Group()
{
	for (size_t i = 0; i < m_Renderables.size(); i++)
		delete m_Renderables[i];
}

void Group::add(Renderable2D* renderable)
{
	m_Renderables.push_back(renderable);
}

void Group::submit(Renderer2D* renderer) const
{
	renderer->push(m_Transformation);

	for (const Renderable2D* renderable : m_Renderables)
		renderable->submit(renderer);

	renderer->pop();
}