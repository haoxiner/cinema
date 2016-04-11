#pragma once
#include <vector>
#include "Point.h"
#include "Geometry.h"
#include "Vector.h"
class Ray;
class Intersection;
class TriangleMesh;
class Triangle : public Geometry
{
public:
	Triangle();
	virtual ~Triangle();
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection);
	virtual Vector GetNormal(const Point & point, const double u1, const double u2)const;
	unsigned int *v;
	TriangleMesh *mesh;
};

class TriangleMesh : public Geometry
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	std::vector<unsigned int> indices;
	std::vector<Point> vertices;
	std::vector<Vector> normals;
	std::vector<float> uvs;
	std::vector<Triangle> triangles;
	virtual bool Intersect(const Ray &ray, double *t, Intersection *intersection);
};
