#pragma once
#include "Material.h"
#include "Geometry.h"
#include "Color.h"
class Ray;
class Intersection;

class Model
{
public:
	Model();
	~Model();
	bool Intersect(const Ray &ray, double *t, Intersection *intersection);
	// one material per model.
	BSDF *bsdf;
	Color emit;
	Geometry *geometry;
};

