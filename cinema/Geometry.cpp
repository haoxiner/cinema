#include "Geometry.h"
#include "Point.h"
Geometry::Geometry()
{
}

Geometry::~Geometry()
{

}

bool Geometry::Intersect(const Ray & ray, double * t, Intersection * intersection)
{
	return false;
}

Vector Geometry::GetNormal(const Intersection & intersection) const
{
	return Vector(0, 0, 1);
}

void Geometry::Extract(std::vector<Geometry*>* geometries)
{
	geometries->push_back(this);
}

