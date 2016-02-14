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
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m_matrix[0][0] = a00;m_matrix[0][1] = a01;m_matrix[0][2] = a02;m_matrix[0][3] = a03;
	m_matrix[1][0] = a10;m_matrix[1][1] = a11;m_matrix[1][2] = a12;m_matrix[1][3] = a13;
	m_matrix[2][0] = a20;m_matrix[2][1] = a21;m_matrix[2][2] = a22;m_matrix[2][3] = a23;
	m_matrix[3][0] = a30;m_matrix[3][1] = a31;m_matrix[3][2] = a32;m_matrix[3][3] = a33;
}


Transform::~Transform()
{
}

Vector Transform::operator()(const Vector & v)
{
	return Vector(
		m_matrix[0][0] * v.x + m_matrix[0][1] * v.y + m_matrix[0][2] * v.z,
		m_matrix[1][0] * v.x + m_matrix[1][1] * v.y + m_matrix[1][2] * v.z,
		m_matrix[2][0] * v.x + m_matrix[2][1] * v.y + m_matrix[2][2] * v.z);
}

Point Transform::operator()(const Point & p)
{
	float invW = 1.0f / (m_matrix[3][0] * p.x + m_matrix[3][1] * p.y + m_matrix[3][2] * p.z + m_matrix[3][3]);
	return Point(
		invW*(m_matrix[0][0] * p.x + m_matrix[0][1] * p.y + m_matrix[0][2] * p.z + m_matrix[0][3]),
		invW*(m_matrix[1][0] * p.x + m_matrix[1][1] * p.y + m_matrix[1][2] * p.z + m_matrix[1][3]),
		invW*(m_matrix[2][0] * p.x + m_matrix[2][1] * p.y + m_matrix[2][2] * p.z + m_matrix[2][3]));
}