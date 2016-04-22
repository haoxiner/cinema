#include "BBox.h"
#include "Ray.h"
#include <limits>
#include <utility>

BBox::BBox()
{
	min.x = min.y = min.z = -std::numeric_limits<double>::infinity();
	max.x = max.y = max.z = std::numeric_limits<double>::infinity();
}

BBox::BBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) :min(minX, minY, minZ), max(maxX, maxY, maxZ)
{
}

BBox::~BBox()
{
}

BBox & BBox::Union(const BBox & b)
{
	min.x = std::fmin(min.x, b.min.x);
	min.y = std::fmin(min.y, b.min.y);
	min.z = std::fmin(min.z, b.min.z);

	max.x = std::fmax(max.x, b.max.x);
	max.y = std::fmax(max.y, b.max.y);
	max.z = std::fmax(max.z, b.max.z);
	return *this;
}

BBox & BBox::Union(const Point & p)
{
	min.x = std::fmin(min.x, p.x);
	min.y = std::fmin(min.y, p.y);
	min.z = std::fmin(min.z, p.z);

	max.x = std::fmax(max.x, p.x);
	max.y = std::fmax(max.y, p.y);
	max.z = std::fmax(max.z, p.z);
	return *this;
}

BBox & BBox::Union(const double x, const double y, const double z)
{
	min.x = std::fmin(min.x, x);
	min.y = std::fmin(min.y, y);
	min.z = std::fmin(min.z, z);

	max.x = std::fmax(max.x, x);
	max.y = std::fmax(max.y, y);
	max.z = std::fmax(max.z, z);
	return *this;
}

bool BBox::Intersect(const Ray & ray) const
{
	double t0 = 1e-7;
	double t1 = std::numeric_limits<double>::infinity();
	for (size_t i = 0; i < 3; ++i)
	{
		double invRayDir = 1.0 / ray.d[i];
		double tNear = (min[i] - ray.o[i]);
		double tFar = (max[i] - ray.o[i]);
		if (tNear > tFar)
		{
			std::swap(tNear, tFar);
		}
		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar < t1 ? tFar : t1;
		if (t0 > t1)
		{
			return false;
		}
	}
	return true;
}
