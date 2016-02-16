#pragma once
#include <vector>
#include "Point.h"
#include "Model.h"
class TriangleMesh : public Model
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	std::vector<unsigned int> indices;
	std::vector<Point> vertices;
	virtual bool Intersect(const Ray &ray, float *t);
};