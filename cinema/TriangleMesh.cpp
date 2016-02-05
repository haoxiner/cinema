#include "TriangleMesh.h"
#include "Triangle.h"


TriangleMesh::TriangleMesh()
{
}


TriangleMesh::~TriangleMesh()
{
}

float TriangleMesh::Intersect(const Ray &ray)
{
	Triangle triangle;
	float t = 0.0f;
	for (auto indexIter = indices.begin(); indexIter != indices.end(); ++indexIter)
	{
		triangle.v1 = vertices[*indexIter];
		++indexIter;
		triangle.v2 = vertices[*indexIter];
		++indexIter;
		triangle.v3 = vertices[*indexIter];
		float tHit = triangle.Intersect(ray);
		if (tHit - t < 0.001f)
		{
			t = tHit;
		}
	}
	return t;
}