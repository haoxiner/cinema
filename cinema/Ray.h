#pragma once
#include "Vector.h"

class Ray
{
public:
	Ray();
	Ray(const Vector &origin, const Vector &direction);
	~Ray();
	Vector o;
	Vector d;
	float t;
};
