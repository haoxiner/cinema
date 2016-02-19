#pragma once
#include "Vector.h"
#include "Point.h"
#include "Color.h"
class Model;
class Intersection
{
public:
	Intersection();
	~Intersection();
	Vector normal;
	Point point;
	Model *model;
	Color color;
};

