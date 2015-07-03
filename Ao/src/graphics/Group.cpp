#include "Group.h"
#include "Renderer2D.h"
#include "../math/AoMath.h"

Group::Group()
{
	m_Transformation = mat4::identity();
	m_Origin = vec3(0.0f, 0.0f, 0.0f);
}

Group::Group(const mat4& matrix)
{
	m_Transformation = matrix;
	m_Origin = vec3(0.0f, 0.0f, 0.0f);
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
	m_Transformation = m_Transformation * mat4::translation(x, y, z);
}

void Group::translate(const vec3& amount)
{
	m_Transformation = m_Transformation * mat4::translation(amount);
}

void Group::rotate(const vec3& axis, float degrees)
{
	m_Transformation = m_Transformation * mat4::translation(m_Origin) * mat4::rotation(axis, degrees) * mat4::translation(-m_Origin);
}