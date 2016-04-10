#pragma once
#include "BSDF.h"
class SpecularReflection : public BSDF
{
public:
	SpecularReflection();
	SpecularReflection(const Color &color);
	~SpecularReflection();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler *sampler);
};

