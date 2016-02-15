#pragma once
#include "Model.h"
#include "Vector.h"
#include "Point.h"
class Triangle : public Model
{
public:
	Triangle();
	virtual ~Triangle();
	virtual bool Intersect(const Ray &ray,float *t);
	Point p0, p1, p2;
};

