#pragma once
#include "Vector.h"
#include "BBox.h"
#include <vector>
class Ray;
class Intersection;
class Point;
class Model;
class Geometry
{
public:
	Geometry();
	virtual ~Geometry() = 0;
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection);
	virtual Vector GetNormal(const Intersection & intersection)const;
	virtual void Extract(std::vector<Geometry*> *geometries);
	Model *model;
	BBox bbox;
};

