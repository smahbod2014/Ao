#include "vec3.h"

vec3::vec3()
{
	x = y = z = 0.0f;
}

vec3::vec3(float x)
{
	this->x = this->y = this->z = x;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::~vec3()
{

}

vec3 operator+(const vec3& a, const vec3& b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 operator+(const vec3& a, float b)
{
	return vec3(a.x + b, a.y + b, a.z + b);
}

vec3 operator-(const vec3& a, const vec3& b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 operator-(const vec3& a, float b)
{
	return vec3(a.x - b, a.y - b, a.z - b);
}

vec3 operator*(const vec3& a, float b)
{
	return vec3(a.x * b, a.y * b, a.z * b);
}

vec3 operator/(const vec3& a, float b)
{
	return vec3(a.x / b, a.y / b, a.z / b);
}

vec3 operator-(const vec3& a)
{
	return vec3(-a.x, -a.y, -a.z);
}

void vec3::operator+=(const vec3& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
}

void vec3::operator+=(float b)
{
	x += b;
	y += b;
	z += b;
}

void vec3::operator-=(const vec3& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
}

void vec3::operator-=(float b)
{
	x -= b;
	y -= b;
	z -= b;
}

void vec3::operator*=(float b)
{
	x *= b;
	y *= b;
	z *= b;
}

void vec3::operator/=(float b)
{
	x /= b;
	y /= b;
	z /= b;
}
