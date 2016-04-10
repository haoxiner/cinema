#pragma once
#include "Geometry.h"
#include "Vector.h"
#include "Point.h"
class Triangle : public Geometry
{
public:
	Triangle();
	virtual ~Triangle();
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection);
	Point p0, p1, p2;
};

