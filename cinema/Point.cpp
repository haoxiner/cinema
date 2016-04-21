#include "Point.h"
#include "Vector.h"


Point::Point()
{
}

Point::Point(double xx, double yy, double zz) :x(xx), y(yy), z(zz)
{
}

Point::~Point()
{
}

Point Point::operator+(const Vector &v) const
{
	return Point(x + v.x, y + v.y, z + v.z);
}

Point Point::operator-(const Vector &v) const
{
	return Point(x - v.x, y - v.y, z - v.z);
}

Vector Point::operator+(const Point & p) const
{
	return Vector(x + p.x, y + p.y, z + p.z);
}

Vector Point::operator-(const Point & p) const
{
	return Vector(x - p.x, y - p.y, z - p.z);
}

double Point::operator[](const size_t index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	return z;
}
