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
	size_t index = 0u;
	float t = 0.0f;
	for (auto indexIter = indices.begin(); indexIter != indices.end(); ++indexIter)
	{
		triangle.p0 = vertices[*indexIter];
		++indexIter;
		triangle.p1 = vertices[*indexIter];
		++indexIter;
		triangle.p2 = vertices[*indexIter];
		float tHit;
		bool hit = triangle.Intersect(ray, &t);
		if (tHit - t < 0.001f)
		{
			t = tHit;
			index = indexIter - indices.begin();
		}
	}
	return t;
}