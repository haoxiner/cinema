#pragma once
#include "Vector.h"
class Point;
class Transform
{
public:
	Transform();
	Transform(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);
	~Transform();
	Vector operator()(const Vector &v);
	Point operator()(const Point &p);
	void SetMatrix(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);
private:
	float m_matrix[4][4];
};

