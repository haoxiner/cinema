#include "SpecularTransmission.h"



SpecularTransmission::SpecularTransmission()
{
}

SpecularTransmission::SpecularTransmission(const Color & color) :BSDF(color)
{
}


SpecularTransmission::~SpecularTransmission()
{
}

Color SpecularTransmission::f(const Vector & normal, const Vector & wo, Vector * wi, double * pdf, Sampler & sampler)
{
	return Color();
}
