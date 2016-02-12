#pragma once
#include "Model.h"
#include "Vector.h"

class Triangle : public Model
{
public:
	Triangle();
	~Triangle();
	virtual bool Intersect(const Ray &ray,float *t);
	Vector p0, p1, p2;
};

