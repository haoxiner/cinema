#include "TriangleMesh.h"
#include "Triangle.h"
#include "Intersection.h"
#include "Ray.h"

TriangleMesh::TriangleMesh()
{
}


TriangleMesh::~TriangleMesh()
{
}

bool TriangleMesh::Intersect(const Ray &ray, double *t, Intersection *intersection)
{
	
	return true;
}

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

bool Triangle::Intersect(const Ray &ray, double *t, Intersection *intersection)
{
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
	*t = Vector::Dot(s2, e2) / determinantOfCoefficient;
	intersection->u1 = b1;
	intersection->u2 = b2;
	intersection->geometry = this;
	return true;
}

Vector Triangle::GetNormal(const Point & point, const double u1, const double u2) const
{
	return mesh->normals[v[2]] * u1 + mesh->normals[v[5]] * u2 + mesh->normals[v[8]] * (1 - u1 - u2);
}
