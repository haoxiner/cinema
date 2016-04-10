#include "Ray.h"
#include "Point.h"

Ray::Ray()
{
}

Ray::Ray(const Point & origin, const Vector & direction) :o(origin), d(direction)
{
}

Ray::~Ray()
{
}

Point Ray::GetPoint(double t) const
{
	return o + d*t;
}
