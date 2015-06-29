#pragma once

#include "vec3.h"

//not yet finished
#if 0
class mat4
{
public:
	mat4();
	~mat4();

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspect, float near, float far);
	
	friend mat4 operator*(const mat4& a, const mat4& b);
	friend vec3 operator*(const mat4& a, const vec3& b);
	friend vec3 operator/(const mat4& a, const vec3& b);

	static mat4 identity();
};
#endif