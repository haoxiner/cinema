#pragma once
#include "Material.h"
#include "Geometry.h"
class Ray;
class Intersection;

class Model
{
public:
	Model();
	~Model();
	bool Intersect(const Ray &ray, float *t, Intersection *intersection);
	// one material per model.
	BSDF *bsdf;
	Geometry *geometry;
};

