#include "Ray.h"
#include "Point.h"

Ray::Ray()
{
}

Ray::Ray(const Vector & origin, const Vector & direction) :o(origin), d(direction)
{
}

Ray::~Ray()
{
}

Point Ray::GetPoint(float t)
{
	Vector v(o + d*t);
	return Point(v.x, v.y, v.z);
}
