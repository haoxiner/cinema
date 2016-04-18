#include "SpecularReflection.h"
#include "Vector.h"
#include <cmath>
SpecularReflection::SpecularReflection()
{
}

SpecularReflection::SpecularReflection(const Color &color):BSDF(color)
{
}

SpecularReflection::~SpecularReflection()
{
}

Color SpecularReflection::f(const Vector & normal, const Vector & wo, Vector * wi, double * pdf, Sampler &sampler)
{
	Vector n = Vector::Dot(normal, wo) >= 0 ? normal : -normal;
	*wi = n * (2 * Vector::Dot(wo, n)) - wo;
	*pdf = 1.0f;
	return  m_color*(1.0 / std::fabs(Vector::Dot(normal, *wi)));
}
