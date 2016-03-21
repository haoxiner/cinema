#include "Sphere.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include <cmath>

Sphere::Sphere(const Point &center,const float radius):
	m_center(center),m_radius(radius),m_squareRadius(radius*radius)
{
}


Sphere::~Sphere()
{
}
#include <cstdio>
bool Sphere::Intersect(const Ray & ray, float * t, Intersection *intersection)
{
	Vector v = ray.o - m_center;
	float vDotD = Vector::Dot(v, ray.d);
	float squareD = ray.d.Square();
	float delta = vDotD*vDotD - squareD*v.Square() + squareD*m_squareRadius;
	if (delta >= 0)
	{
		*t = (-vDotD - std::sqrtf(delta)) / squareD;
		if (*t > 0.0f)
		{
			intersection->point = ray.GetPoint(*t);
			intersection->normal = intersection->point - m_center;
			return true;
		}
	}
	return false;
}
