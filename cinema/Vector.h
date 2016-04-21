#pragma once

class Vector
{
public:
	double x, y, z;
	Vector();
	Vector(const double xx, const double yy, const double zz);
	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator-()const;
	Vector operator*(const double f) const;
	Vector operator/(const double f) const;
	Vector & operator-=(const Vector &v);
	Vector & operator-=(const double f);
	double operator[](const size_t index)const;
	double Square() const;
	Vector Normalize()const;
	static Vector Cross(const Vector &v1, const Vector &v2);
	static double Dot(const Vector &v1, const Vector &v2);
	static Vector Normalize(const Vector &v);
};
