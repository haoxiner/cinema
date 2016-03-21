#include "Vector.h"
#include <cmath>
Vector::Vector() :x(0.0f), y(0.0f), z(0.0f) {}
Vector::Vector(const float xx, const float yy, const float zz) : x(xx), y(yy), z(zz) {}

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}
Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}
Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}
Vector Vector::operator*(const float f) const
{
	return Vector(x*f, y*f, z*f);
}
Vector Vector::operator/(const float f) const
{
	float fInv = 1.0f / f;
	return Vector(x*fInv, y*fInv, z*fInv);
}
float Vector::Square() const
{
	return x*x + y*y + z*z;
}
Vector Vector::Normalize() const
{
	return Vector::Normalize(*this);
}
Vector Vector::Cross(const Vector &v1, const Vector &v2)
{
	return Vector(v1.y*v2.z - v2.y*v1.z, v2.x*v1.z - v1.x*v2.z, v1.x*v2.y - v2.x*v1.y);
}
float Vector::Dot(const Vector &v1, const Vector &v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector Vector::Normalize(const Vector & v)
{
	float invLength = 1.0f / std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	return Vector(v.x*invLength, v.y*invLength, v.z*invLength);
}
