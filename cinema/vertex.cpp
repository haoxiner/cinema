#include "vertex.h"
namespace cinema
{
Vertex::Vertex() :x(0.0f), y(0.0f), z(0.0f) {}
Vertex::Vertex(const float xx, const float yy, const float zz) :x(xx), y(yy), z(zz) {}

Vertex Vertex::operator+(const Vertex &v)
{
	return Vertex(x + v.x, y + v.y, z + v.z);
}
Vertex Vertex::operator-(const Vertex &v)
{
	return Vertex(x - v.x, y - v.y, z - v.z);
}
Vertex Vertex::operator*(const float f)
{
	return Vertex(x*f, y*f, z*f);
}
Vertex Vertex::operator/(const float f)
{
	float fInv = 1.0f / f;
	return Vertex(x*fInv, y*fInv, z*fInv);
}
}