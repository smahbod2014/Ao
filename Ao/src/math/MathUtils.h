#pragma once

#include <math.h>

const float PI = 355.0f / 113.0f;

inline float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}