#include "Group.h"
#include "Renderer2D.h"
#include <glm/gtx/transform.hpp>

Group::Group()
{
	m_Transformation = glm::mat4(1.0f);
	m_Origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

Group::Group(const glm::mat4& matrix)
{
	m_Transformation = matrix;
	m_Origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

Group::~Group()
{
	for (size_t i = 0; i < m_Renderables.size(); i++)
		delete m_Renderables[i];

	m_Renderables.clear();
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

void Group::setOrigin(float x, float y)
{
	m_Origin.x = x;
	m_Origin.y = y;
}

void Group::translate(float x, float y, float z)
{
	m_Transformation = glm::translate(m_Transformation, glm::vec3(x, y, z));
}

void Group::translate(const glm::vec3& amount)
{
	m_Transformation = glm::translate(m_Transformation, amount);
}

void Group::rotate(const glm::vec3& axis, float degrees)
{
	glm::mat4 invTrans = glm::translate(m_Transformation, m_Origin);
	glm::mat4 rotation = glm::rotate(invTrans, glm::radians<float>(degrees), axis);
	m_Transformation = glm::translate(rotation, -m_Origin);
}