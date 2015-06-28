#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Renderable2D.h"

struct Texture;

class Sprite : public Renderable2D
{
public:
	Sprite(const glm::vec3& position);
	Sprite(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	Sprite(const glm::vec3& position, const Texture* texture);
	Sprite(const glm::vec3& position, const glm::vec2& size, const Texture* texture);
	Sprite(const glm::vec3& position, const glm::vec2& size, unsigned int color, const Texture* texture);
	virtual ~Sprite() {}
public:
	glm::vec3& position;
};