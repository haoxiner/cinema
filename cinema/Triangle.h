#pragma once
#include "Geometry.h"
#include "Vector.h"
#include "Point.h"
class Ray;
class Intersection;
class TriangleMesh;
class Triangle : public Geometry
{
public:
	Triangle();
	virtual ~Triangle();
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection);
	virtual Vector GetNormal(const Intersection & intersection)const;
	unsigned int *v;
	TriangleMesh *mesh;
};