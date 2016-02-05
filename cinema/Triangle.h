#pragma once
#include "Model.h"
#include "Vector.h"

class Triangle : public Model
{
public:
	Triangle();
	~Triangle();
	virtual float Intersect(const Ray &ray);

	Vector v1, v2, v3;
};

