#pragma once

struct Vector
{
	float x, y, z;
	Vector();
	Vector(const float xx, const float yy, const float zz);
	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator-()const;
	Vector operator*(const float f) const;
	Vector operator/(const float f) const;
	float Square() const;
	static Vector Cross(const Vector &v1, const Vector &v2);
	static float Dot(const Vector &v1, const Vector &v2);
	static Vector Normalize(const Vector &v);
};
