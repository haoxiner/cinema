#pragma once
#include "Vector.h"
#include "Point.h"
class Ray
{
public:
	Ray();
	Ray(const Vector &origin, const Vector &direction);
	~Ray();
	Vector o;
	Vector d;
	float t;
	Point GetPoint(float t);
};
