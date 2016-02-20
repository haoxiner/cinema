#pragma once
class Ray;
class Intersection;
class Geometry
{
public:
	Geometry();
	virtual ~Geometry() = 0;
	virtual bool Intersect(const Ray &ray, float *t, Intersection *intersection) = 0;
};

