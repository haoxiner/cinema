#pragma once
#include "Geometry.h"
#include "Point.h"
class Sphere : public Geometry
{
public:
	Sphere(const Point &center, const double radius);
	virtual ~Sphere();
	virtual bool Intersect(const Ray &ray, double *t,Intersection *intersection);
	virtual Vector GetNormal(const Intersection & intersection)const;
private:
	Point m_center;
	double m_radius;
	double m_squareRadius;
};

