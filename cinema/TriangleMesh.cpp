#include "TriangleMesh.h"
#include "Triangle.h"
#include "Intersection.h"

TriangleMesh::TriangleMesh()
{
}


TriangleMesh::~TriangleMesh()
{
}

bool TriangleMesh::Intersect(const Ray &ray, float *t, Intersection *intersection)
{
	Triangle triangle;
	size_t index = 0u;
	for (auto indexIter = indices.begin(); indexIter != indices.end(); ++indexIter)
	{
		triangle.p0 = vertices[*indexIter];
		++indexIter;
		triangle.p1 = vertices[*indexIter];
		++indexIter;
		triangle.p2 = vertices[*indexIter];
		float tHit;
		/*bool hit = triangle.Intersect(ray, &t);
		if (tHit - t < 0.001f)
		{
			t = tHit;
			index = indexIter - indices.begin();
		}*/
	}
	return true;
}