#pragma once
#include "Vector.h"
#include "Point.h"
#include "Color.h"
class Model;
class Geometry;
class Intersection
{
public:
	Intersection();
	~Intersection();
	Vector normal;
	Point point;
	Model *model;
	Color color;
	double u1, u2;
	float u, v;
	Geometry *geometry;
};

