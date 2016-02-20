#include "Model.h"

Model::Model():geometry(nullptr)
{
}

Model::~Model()
{
	if (geometry != nullptr)
	{
		delete geometry;
	}
}

bool Model::Intersect(const Ray &ray, float *t, Intersection *intersection)
{
	return geometry->Intersect(ray, t, intersection);
}