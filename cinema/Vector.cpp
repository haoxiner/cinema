#include "Vector.h"

Vector::Vector() :x(0.0f), y(0.0f), z(0.0f) {}
Vector::Vector(const float xx, const float yy, const float zz) : x(xx), y(yy), z(zz) {}

Vector Vector::operator+(const Vector &v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator-(const Vector &v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}
Vector Vector::operator*(const float f)
{
	return Vector(x*f, y*f, z*f);
}
Vector Vector::operator/(const float f)
{
	float fInv = 1.0f / f;
	return Vector(x*fInv, y*fInv, z*fInv);
}

