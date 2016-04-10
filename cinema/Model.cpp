#include "Model.h"
#include "Intersection.h"
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

bool Model::Intersect(const Ray &ray, double *t, Intersection *intersection)
{
	if (geometry->Intersect(ray, t, intersection))
	{
		intersection->model = this;
		return true;
	}
	return false;
}

