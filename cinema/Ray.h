#pragma once
#include "Vector.h"

class Ray
{
public:
	Ray();
	~Ray();
	Vector o;
	Vector d;
	float t;
};
