#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Renderable2D.h"

class Renderer2D;

class Group : public Renderable2D
{
public:
	Group(const glm::mat4& matrix);
	~Group();

	void add(Renderable2D* renderable);
	virtual void submit(Renderer2D* renderer) const override;
private:
	std::vector<Renderable2D*> m_Renderables;
	glm::mat4 m_Transformation;
};