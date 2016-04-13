#pragma once
#include "Material.h"
#include "Geometry.h"
#include "Color.h"
#include <vector>
class Ray;
class Intersection;
class Material;
class Model
{
public:
	Model();
	~Model();
	// one material per model.
	BSDF *bsdf;
	Color emit;
	void GetGeometries(std::vector<Geometry*> *geometries);
	void AddGeometry(Geometry *geometry);
private:
	std::vector<Geometry*> m_geometries;
};

