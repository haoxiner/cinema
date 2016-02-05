#pragma once
#include <vector>
#include "Vector.h"
#include "Model.h"
class TriangleMesh : public Model
{
public:
	TriangleMesh();
	~TriangleMesh();
	std::vector<unsigned int> indices;
	std::vector<Vector> vertices;
	virtual float Intersect(const Ray &ray);
};