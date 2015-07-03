#include "vec2.h"

vec2::vec2()
{
	x = y = 0.0f;
}

vec2::vec2(float x)
{
	this->x = this->y = x;
}

vec2::vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

vec2::~vec2()
{

}

vec2 operator+(const vec2& a, const vec2& b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator+(const vec2& a, float b)
{
	return vec2(a.x + b, a.y + b);
}

vec2 operator-(const vec2& a, const vec2& b)
{
	return vec2(a.x - b.x, a.y - b.y);
}

vec2 operator-(const vec2& a, float b)
{
	return vec2(a.x - b, a.y - b);
}

vec2 operator*(const vec2& a, float b)
{
	return vec2(a.x * b, a.y * b);
}

vec2 operator/(const vec2& a, float b)
{
	return vec2(a.x / b, a.y / b);
}

vec2 operator-(const vec2& a)
{
	return vec2(-a.x, -a.y);
}

void vec2::operator+=(const vec2& a)
{
	x += a.x;
	y += a.y;
}

void vec2::operator+=(float b)
{
	x += b;
	y += b;
}

void vec2::operator-=(const vec2& a)
{
	x -= a.x;
	y -= a.y;
}

void vec2::operator-=(float b)
{
	x -= b;
	y -= b;
}

void vec2::operator*=(float b)
{
	x *= b;
	y *= b;
}

void vec2::operator/=(float b)
{
	x /= b;
	y /= b;
}