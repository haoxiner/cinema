#include "Triangle.h"
#include "Ray.h"
#include "Vector.h"

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}
#include <iostream>
bool Triangle::Intersect(const Ray &ray,float *t)
{
	static unsigned int cnt = 0;

	Vector s = ray.o - p0;
	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;
	Vector s1 = Vector::Cross(ray.d, e2);
	Vector s2 = Vector::Cross(s, e1);
	float determinantOfCoefficient = Vector::Dot(s1, e1);
	if (determinantOfCoefficient - 0.0f < 0.0001f)
	{
		return false;
	}
	float b1 = Vector::Dot(s1, s) / determinantOfCoefficient;
	std::cerr << b1 << std::endl;
	if (b1 > 1.0f || b1 < 0.0f)
	{
		return false;
	}
	float b2 = Vector::Dot(s2, ray.d) / determinantOfCoefficient;
	if (b2 > 1.0f || b2 < 0.0f)
	{
		++cnt;
		std::cerr << cnt << " ";
		return false;
	}
	*t = Vector::Dot(s2, e2) / determinantOfCoefficient;
	return true;
}