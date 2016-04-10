#include "Transform.h"
#include "Point.h"


Transform::Transform()
{
	m_matrix[0][0] = 1;m_matrix[0][1] = 0;m_matrix[0][2] = 0;m_matrix[0][3] = 0;
	m_matrix[1][0] = 0;m_matrix[1][1] = 1;m_matrix[1][2] = 0;m_matrix[1][3] = 0;
	m_matrix[2][0] = 0;m_matrix[2][1] = 0;m_matrix[2][2] = 1;m_matrix[2][3] = 0;
	m_matrix[3][0] = 0;m_matrix[3][1] = 0;m_matrix[3][2] = 0;m_matrix[3][3] = 1;
}

Transform::Transform(
	double a00, double a01, double a02, double a03,
	double a10, double a11, double a12, double a13,
	double a20, double a21, double a22, double a23,
	double a30, double a31, double a32, double a33)
{
	m_matrix[0][0] = a00;m_matrix[0][1] = a01;m_matrix[0][2] = a02;m_matrix[0][3] = a03;
	m_matrix[1][0] = a10;m_matrix[1][1] = a11;m_matrix[1][2] = a12;m_matrix[1][3] = a13;
	m_matrix[2][0] = a20;m_matrix[2][1] = a21;m_matrix[2][2] = a22;m_matrix[2][3] = a23;
	m_matrix[3][0] = a30;m_matrix[3][1] = a31;m_matrix[3][2] = a32;m_matrix[3][3] = a33;
}


Transform::~Transform()
{
}

Vector Transform::operator()(const Vector & v)const
{
	return Vector(
		m_matrix[0][0] * v.x + m_matrix[0][1] * v.y + m_matrix[0][2] * v.z,
		m_matrix[1][0] * v.x + m_matrix[1][1] * v.y + m_matrix[1][2] * v.z,
		m_matrix[2][0] * v.x + m_matrix[2][1] * v.y + m_matrix[2][2] * v.z);
}

Point Transform::operator()(const Point & p)const
{
	double invW = 1.0f / (m_matrix[3][0] * p.x + m_matrix[3][1] * p.y + m_matrix[3][2] * p.z + m_matrix[3][3]);
	return Point(
		invW*(m_matrix[0][0] * p.x + m_matrix[0][1] * p.y + m_matrix[0][2] * p.z + m_matrix[0][3]),
		invW*(m_matrix[1][0] * p.x + m_matrix[1][1] * p.y + m_matrix[1][2] * p.z + m_matrix[1][3]),
		invW*(m_matrix[2][0] * p.x + m_matrix[2][1] * p.y + m_matrix[2][2] * p.z + m_matrix[2][3]));
}

Transform Transform::operator*(const Transform & t) const
{
	Transform ret;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			ret.m_matrix[i][j] =
				m_matrix[i][0] * t.m_matrix[0][j] +
				m_matrix[i][1] * t.m_matrix[1][j] +
				m_matrix[i][2] * t.m_matrix[2][j] +
				m_matrix[i][3] * t.m_matrix[3][j];
		}
	}
	return ret;
}

void Transform::SetMatrix(
	double a00, double a01, double a02, double a03,
	double a10, double a11, double a12, double a13,
	double a20, double a21, double a22, double a23,
	double a30, double a31, double a32, double a33)
{
	m_matrix[0][0] = a00;m_matrix[0][1] = a01;m_matrix[0][2] = a02;m_matrix[0][3] = a03;
	m_matrix[1][0] = a10;m_matrix[1][1] = a11;m_matrix[1][2] = a12;m_matrix[1][3] = a13;
	m_matrix[2][0] = a20;m_matrix[2][1] = a21;m_matrix[2][2] = a22;m_matrix[2][3] = a23;
	m_matrix[3][0] = a30;m_matrix[3][1] = a31;m_matrix[3][2] = a32;m_matrix[3][3] = a33;
}
