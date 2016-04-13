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

