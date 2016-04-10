#pragma once
#include "Vector.h"
class Point;
class Transform
{
public:
	Transform();
	Transform(
		double a00, double a01, double a02, double a03,
		double a10, double a11, double a12, double a13,
		double a20, double a21, double a22, double a23,
		double a30, double a31, double a32, double a33);
	~Transform();
	Vector operator()(const Vector &v)const;
	Point operator()(const Point &p)const;
	Transform operator*(const Transform &t)const;
	void SetMatrix(
		double a00, double a01, double a02, double a03,
		double a10, double a11, double a12, double a13,
		double a20, double a21, double a22, double a23,
		double a30, double a31, double a32, double a33);
private:
	double m_matrix[4][4];
};

