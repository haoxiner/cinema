#pragma once
#include "Color.h"
class Vector;
class BxDF
{
public:
	BxDF();
	~BxDF();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, float u1, float u2, float *pdf) = 0;
};

