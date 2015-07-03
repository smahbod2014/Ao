#pragma once

#include <vector>
#include "../math/AoMath.h"

class Renderer2D;
class Renderable2D;
class Shader;

class Layer
{
public:
	Layer(Renderer2D* renderer, Shader* shader, const mat4& projection);
	virtual ~Layer();

	virtual void add(Renderable2D* renderable);
	virtual void render();
private:
	mat4 m_Projection;
	Renderer2D* m_Renderer;
	Shader* m_Shader;
	std::vector<Renderable2D*> m_Renderables;
};