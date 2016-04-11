#pragma once
#include "Vector.h"
class Ray;
class Intersection;
class Point;
class Geometry
{
public:
	Geometry();
	virtual ~Geometry() = 0;
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection) = 0;
	virtual Vector GetNormal(const Point &point, const double u1, const double u2)const;
};

