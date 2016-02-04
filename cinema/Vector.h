#pragma once

struct Vector
{
	float x, y, z;
	Vector();
	Vector(const float xx, const float yy, const float zz);
	Vector operator+(const Vector &v);
	Vector operator-(const Vector &v);
	Vector operator*(const float f);
	Vector operator/(const float f);
};
