#include "Transform.h"



Transform::Transform()
{
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
