#pragma once
#include "Vector.h"
class Transform
{
public:
	Transform();
	~Transform();
	Vector operator()(const Vector &v);
private:
	float m_matrix[4][4];
};

