#pragma once
#include "Color.h"
class Vector;
class Sampler;
class BSDF
{
public:
	BSDF();
	BSDF(const Color &color);
	~BSDF();
	virtual Color f(const Vector &normal, const Vector &wo, Vector *wi, double *pdf, Sampler *sampler) = 0;
protected:
	Color m_color;
};

