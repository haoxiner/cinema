#pragma once
#include <vector>
#include "Point.h"
#include "Geometry.h"

class TriangleMesh : public Geometry
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	std::vector<unsigned int> indices;
	std::vector<Point> vertices;
	virtual bool Intersect(const Ray &ray, float *t, Intersection *intersection);
};