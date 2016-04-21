#include "Sphere.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include <cmath>

Sphere::Sphere(const Point &center,const double radius):
	m_center(center),m_radius(radius),m_squareRadius(radius*radius)
{
	bbox.Union(center.x + radius, center.y + radius, center.z + radius);
	bbox.Union(center.x - radius, center.y - radius, center.z - radius);
}


Sphere::~Sphere()
{
}

bool Sphere::Intersect(const Ray & ray, double * t, Intersection *intersection)
{
	if (!bbox.Intersect(ray))
	{
		return false;
	}
	Vector v = ray.o - m_center;
	double vDotD = Vector::Dot(v, ray.d);
	double squareD = ray.d.Square();
	double delta = vDotD*vDotD - squareD*v.Square() + squareD*m_squareRadius;
	if (delta >= 0)
	{
		double tHit = (-vDotD - std::sqrt(delta)) / squareD;
		if (tHit > 1e-7)
		{
			*t = tHit;
			intersection->geometry = this;
			return true;
		}
	}
	return false;
}

Vector Sphere::GetNormal(const Intersection & intersection)const
{
	return intersection.point - m_center;
}

