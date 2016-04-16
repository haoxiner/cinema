#include "BlinnGlossy.h"
#include "Vector.h"
#include "Sampler.h"
#include <cmath>

BlinnGlossy::BlinnGlossy()
{
}

BlinnGlossy::BlinnGlossy(const Color & color, const double exponent) :BSDF(color), m_exponent(exponent)
{
}


BlinnGlossy::~BlinnGlossy()
{
}
#define M_PI 3.14159265358979323846
Color BlinnGlossy::f(const Vector & normal, const Vector & wo, Vector * wi, double * pdf, Sampler & sampler)
{
	Vector tangent, bitangent;
	if (normal.z < -0.9999999)
	{
		tangent = Vector(0, -1, 0);
		bitangent = Vector(-1, 0, 0);
	}
	else
	{
		const double a = 1.0 / (1.0 + normal.z);
		const double b = -normal.x*normal.y*a;
		tangent = Vector(1.0 - normal.x*normal.x*a, b, -normal.x);
		bitangent = Vector(b, 1.0 - normal.y*normal.y*a, -normal.y);
	}

	const double u1 = sampler.GetDouble();
	const double u2 = sampler.GetDouble();
	const double cosTheta = std::pow(u1, 1.0 / (m_exponent + 1));
	const double sinTheta = std::sqrt(std::fmax(0, 1 - cosTheta*cosTheta));
	const double phi = 2 * u2 * M_PI;

	Vector h = (tangent*(sinTheta*std::cos(phi)) + bitangent*(sinTheta*std::sin(phi)) + normal*cosTheta).Normalize();
	if (Vector::Dot(h,wo) <= 0)
	{
		h = -h;
	}
	
	if (Vector::Dot(wo,h) <= 0.0)
	{
		*pdf = 1.0;
	}
	else
	{
		*wi = h * (2 * Vector::Dot(wo, h)) - wo;
		*pdf = 1.0;
		//*pdf = ((m_exponent + 1.0)*std::pow(cosTheta, m_exponent)) / (2.0*M_PI*4.0*Vector::Dot(wo, h));
	}
	return m_color;
}
