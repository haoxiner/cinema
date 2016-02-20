#pragma once
#include "Geometry.h"
#include "Point.h"
class Sphere : public Geometry
{
public:
	Sphere(const Point &center, const float radius);
	virtual ~Sphere();
	virtual bool Intersect(const Ray &ray, float *t,Intersection *intersection);
private:
	Point m_center;
	float m_radius;
	float m_squareRadius;
};

