#pragma once
#include "Vector.h"
class Point
{
public:
	Point();
	Point(float xx, float yy, float zz);
	~Point();
	Point operator+(const Vector &v) const;
	Point operator-(const Vector &v) const;
	Vector operator+(const Point &p) const;
	Vector operator-(const Point &p) const;
	float x, y, z;
};

