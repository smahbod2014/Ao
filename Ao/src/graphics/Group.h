#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Renderable2D.h"

class Renderer2D;

class Group : public Renderable2D
{
public:
	Group();
	Group(const glm::mat4& matrix);
	~Group();

	void add(Renderable2D* renderable);
	virtual void submit(Renderer2D* renderer) const override;
	
	void setOrigin(float x, float y);
	void translate(float x, float y, float z);
	void translate(const glm::vec3& amount);
	void rotate(const glm::vec3& axis, float degrees);
private:
	std::vector<Renderable2D*> m_Renderables;
	glm::mat4 m_Transformation;
	glm::vec3 m_Origin;
};