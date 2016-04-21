#include "TriangleMesh.h"

TriangleMesh::TriangleMesh()
{
}

TriangleMesh::~TriangleMesh()
{
}

void TriangleMesh::MakeTriangles()
{
	for (size_t i = 0; i < indices.size() / 9; ++i)
	{
		Triangle triangle;
		triangle.v = &indices[i*9];
		triangle.mesh = this;
		triangle.model = model;
		const Point &p0 = vertices[triangle.v[0]];
		const Point &p1 = vertices[triangle.v[3]];
		const Point &p2 = vertices[triangle.v[6]];
		triangle.bbox.Union(p0);
		triangle.bbox.Union(p1);
		triangle.bbox.Union(p2);
		triangles.push_back(triangle);
	}
}

void TriangleMesh::Extract(std::vector<Geometry*>* geometries)
{
	for (auto & triangle : triangles)
	{
		Geometry * geometry = &triangle;
		geometries->push_back(geometry);
	}
}

