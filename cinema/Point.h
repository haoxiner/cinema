#pragma once
#include "Vector.h"
class Point
{
public:
	Point();
	Point(double xx, double yy, double zz);
	~Point();
	Point operator+(const Vector &v) const;
	Point operator-(const Vector &v) const;
	Vector operator+(const Point &p) const;
	Vector operator-(const Point &p) const;
	double x, y, z;
};

