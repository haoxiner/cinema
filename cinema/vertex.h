#pragma once
namespace cinema
{
struct Vertex
{
	float x, y, z;
	Vertex();
	Vertex(const float xx, const float yy, const float zz);
	Vertex operator+(const Vertex &v);
	Vertex operator-(const Vertex &v);
	Vertex operator*(const float f);
	Vertex operator/(const float f);
};
}