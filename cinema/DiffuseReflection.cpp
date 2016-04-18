#include "DiffuseReflection.h"
#include "Vector.h"
#include "Sampler.h"
#include <cmath>
DiffuseReflection::DiffuseReflection()
{
}

DiffuseReflection::DiffuseReflection(const Color & color) :BSDF(color)
{
}
#define M_PI 3.14159265358979323846
Color DiffuseReflection::f(const Vector & normal, const Vector & wo, Vector * wi, double * pdf, Sampler &sampler)
{
	Vector n = Vector::Dot(normal,wo) >= 0 ? normal : -normal;
	/*
	Vector tangent, bitangent;
	if (std::fabs(n.x) > 0.9)
	{
		tangent = Vector(0, 1, 0);
	}
	else
	{
		tangent = Vector(1, 0, 0);
	}
	tangent -= n*Vector::Dot(n, tangent);
	tangent = tangent.Normalize();
	bitangent = Vector::Cross(n, tangent).Normalize();*/

	/*
	 * Frisvad J R. Building an orthonormal basis from a 3D unit vector without normalization[J].
	 * Journal of Graphics Tools, 2012, 16(3): 151-159.
	 */
	Vector tangent, bitangent;
	if (n.z < -0.9999999)
	{
		tangent = Vector(0, -1, 0);
		bitangent = Vector(-1, 0, 0);
	}
	else
	{
		const double a = 1.0 / (1.0 + n.z);
		const double b = -n.x*n.y*a;
		tangent = Vector(1.0 - n.x*n.x*a, b, -n.x);
		bitangent = Vector(b, 1.0 - n.y*n.y*a, -n.y);
	}

	/*
	 * cosine sample vector around normal
	 */
	const double u1 = sampler.GetDouble();
	const double u2 = sampler.GetDouble();
	const double r = std::sqrt(u1);
	const double theta = 2 * M_PI * u2;
	*wi = tangent*(r*std::cos(theta)) + bitangent*(r*std::sin(theta)) + n*std::sqrt(std::fmax(0, 1 - u1));

	/* if return color/PI , then pdf=1.0/PI.
	 * we simplify this by returning color and setting pdf=1.0
	 */
	*pdf = 1.0;
	return m_color;
}
