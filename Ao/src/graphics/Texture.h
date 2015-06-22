#pragma once

#include <GL/glew.h>

struct Texture
{
	Texture(GLuint texID, unsigned long texWidth, unsigned long texHeight) : id(texID), width(texWidth), height(texHeight) {}
	GLuint id;
	unsigned long width, height;
};