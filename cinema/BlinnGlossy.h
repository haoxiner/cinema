#pragma once
#include "BSDF.h"
class BlinnGlossy : public BSDF
{
public:
	BlinnGlossy();
	BlinnGlossy(const Color & color,const double exponent);
	~BlinnGlossy();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler &sampler);
private:
	double m_exponent;
};