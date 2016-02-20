#pragma once
#include "BxDF.h"
class SpecularReflection : public BxDF
{
public:
	SpecularReflection();
	~SpecularReflection();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, float u1, float u2, float *pdf);
};

