#pragma once
#include "Vector.h"
#include "Point.h"
class Ray
{
public:
	Ray();
	Ray(const Point &origin, const Vector &direction);
	~Ray();
	Point o;
	Vector d;
	Point GetPoint(double t) const;
};
