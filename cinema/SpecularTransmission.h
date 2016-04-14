#pragma once
#include "BSDF.h"
class SpecularTransmission : public BSDF
{
public:
	SpecularTransmission();
	SpecularTransmission(const Color &color);
	~SpecularTransmission();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler &sampler);
};

