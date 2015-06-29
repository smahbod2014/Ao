#pragma once

class vec2
{
public:
	vec2();
	vec2(float x);
	vec2(float x, float y);
	~vec2();

	friend vec2 operator+(const vec2& a, const vec2& b);
	friend vec2 operator+(const vec2& a, float b);
	friend vec2 operator-(const vec2& a, const vec2& b);
	friend vec2 operator-(const vec2& a, float b);
	friend vec2 operator*(const vec2& a, float b);
	friend vec2 operator/(const vec2& a, float b);
	void operator+=(const vec2& a);
	void operator+=(float b);
	void operator-=(const vec2& a);
	void operator-=(float b);
	void operator*=(float b);
	void operator/=(float b);
public:
	float x, y;
};