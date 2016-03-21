#include "SpecularReflection.h"
#include "Vector.h"
SpecularReflection::SpecularReflection()
{
}

SpecularReflection::SpecularReflection(const Color &color):BSDF(color)
{
}

SpecularReflection::~SpecularReflection()
{
}

Color SpecularReflection::f(const Vector & normal, const Vector & wo, Vector * wi, float * pdf)
{
	*wi = normal * (2 * Vector::Dot(wo, normal)) - wo;
	*pdf = 1.0f;
	return m_color;
}
