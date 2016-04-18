#pragma once
#include "BSDF.h"
class SpecularTransmission : public BSDF
{
public:
	SpecularTransmission();
	SpecularTransmission(const Color &color,const double eta);
	~SpecularTransmission();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler &sampler);
private:
	double m_eta;
};

