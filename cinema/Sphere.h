#pragma once
#include "Model.h"
#include "Point.h"
class Sphere : public Model
{
public:
	Sphere(const Point &center, const float radius);
	~Sphere();
	virtual bool Intersect(const Ray &ray, float *t);
private:
	Point m_center;
	float m_radius;
	float m_squareRadius;
};

