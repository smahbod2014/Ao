#pragma once

#include <vector>
#include "Renderable2D.h"

class Renderer2D;

class Group : public Renderable2D
{
public:
	Group();
	Group(const mat4& matrix);
	~Group();

	void add(Renderable2D* renderable);
	virtual void submit(Renderer2D* renderer) const override;
	
	void setOrigin(float x, float y);
	void translate(float x, float y, float z);
	void translate(const vec3& amount);
	void rotate(const vec3& axis, float degrees);
private:
	std::vector<Renderable2D*> m_Renderables;
	mat4 m_Transformation;
	vec3 m_Origin;
};