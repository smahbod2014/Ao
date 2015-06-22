#pragma once

#include <vector>
#include <glm/glm.hpp>

class Renderable2D;

class Renderer2D
{
protected:
	Renderer2D();
public:
	virtual ~Renderer2D() {}

	void push(const glm::mat4& matrix);
	void pop();

	virtual void begin() {}
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void end() {}
	virtual void flush() = 0;
protected:
	std::vector<glm::mat4> m_TransformationStack;
	const glm::mat4* m_TransformationBack;
};