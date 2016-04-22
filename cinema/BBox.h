#pragma once
#include "Point.h"
class Ray;
class BBox
{
public:
	BBox();
	BBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
	~BBox();
	Point min, max;
	BBox & Union(const BBox & b);
	BBox & Union(const Point & p);
	BBox & Union(const double x, const double y, const double z);
	bool Intersect(const Ray & ray)const;
	int MaxExtension()const;
	Point GetCenter()const;
};

