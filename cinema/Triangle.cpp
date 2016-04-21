#include "Triangle.h"
#include "Ray.h"
#include "Vector.h"
#include "Intersection.h"
#include "TriangleMesh.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

bool Triangle::Intersect(const Ray &ray, double *t, Intersection *intersection)
{
	if (!bbox.Intersect(ray))
	{
		return false;
	}
	const Point &p0 = mesh->vertices[v[0]];
	const Point &p1 = mesh->vertices[v[3]];
	const Point &p2 = mesh->vertices[v[6]];
	Vector s = ray.o - p0;
	Vector e1 = p1 - p0;
	Vector e2 = p2 - p0;
	Vector s1 = Vector::Cross(ray.d, e2);
	Vector s2 = Vector::Cross(s, e1);
	double determinantOfCoefficient = Vector::Dot(s1, e1);
	// TODO: 0.0 may be a problem
	if (determinantOfCoefficient == 0.0)
	{
		return false;
	}
	double b1 = Vector::Dot(s1, s) / determinantOfCoefficient;
	if (b1 > 1.0 || b1 < 0.0)
	{
		return false;
	}
	double b2 = Vector::Dot(s2, ray.d) / determinantOfCoefficient;
	if (b2 > 1.0 || b2 < 0.0)
	{
		return false;
	}
	if (b1 + b2 > 1.0)
	{
		return false;
	}
	double tHit = Vector::Dot(s2, e2) / determinantOfCoefficient;
	// 0.0 makes mistake because of self-intersection
	if (tHit <= 1e-7)
	{
		return false;
	}
	*t = tHit;
	intersection->u1 = b1;
	intersection->u2 = b2;
	intersection->geometry = this;
	return true;
}

Vector Triangle::GetNormal(const Intersection & intersection) const
{
	double b3 = 1 - intersection.u1 - intersection.u2;
	return mesh->normals[v[2]] * intersection.u1 + mesh->normals[v[5]] * intersection.u2 + mesh->normals[v[8]] * (b3 > 0 ? b3 : 0);
}
