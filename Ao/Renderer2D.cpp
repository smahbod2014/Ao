#include "Renderer2D.h"

Renderer2D::Renderer2D()
{
	m_TransformationStack.push_back(glm::mat4(1.0));
	m_TransformationBack = &m_TransformationStack.back();
}

void Renderer2D::push(const glm::mat4& matrix)
{
	m_TransformationStack.push_back(*m_TransformationBack * matrix);
	m_TransformationBack = &m_TransformationStack.back();
}

void Renderer2D::pop()
{
	if (m_TransformationStack.size() > 1)
	{
		m_TransformationStack.pop_back();
		m_TransformationBack = &m_TransformationStack.back();
	}
}