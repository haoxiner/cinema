#include "DiffuseReflection.h"

DiffuseReflection::DiffuseReflection()
{
}

DiffuseReflection::DiffuseReflection(const Color & color) :BSDF(color)
{
}

Color DiffuseReflection::f(const Vector & normal, const Vector & wo, Vector * wi, float * pdf, Sampler *sampler)
{
	return Color();
}
