#pragma once
#include <vector>
#include "Point.h"
#include "Geometry.h"
#include "Vector.h"
#include "Triangle.h"

class TriangleMesh
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	std::vector<unsigned int> indices;
	std::vector<Point> vertices;
	std::vector<Vector> normals;
	std::vector<float> uvs;
	std::vector<Triangle> triangles;
};
