#pragma once
#include "BSDF.h"
class DiffuseReflection : public BSDF
{
public:
	DiffuseReflection();
	DiffuseReflection(const Color &color);
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler &sampler);
};