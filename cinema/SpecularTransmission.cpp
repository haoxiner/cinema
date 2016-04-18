#include "SpecularTransmission.h"
#include "Vector.h"
#include "Sampler.h"
#include "Fresnel.h"
#include <cmath>

SpecularTransmission::SpecularTransmission()
{
}

SpecularTransmission::SpecularTransmission(const Color & color, double eta) :BSDF(color), m_eta(eta)
{
}


SpecularTransmission::~SpecularTransmission()
{
}

Color SpecularTransmission::f(const Vector & normal, const Vector & wo, Vector * wi, double * pdf, Sampler & sampler)
{
	Vector n = normal;
	double cosPhi = std::fabs(Vector::Dot(n, wo));
	double cosTheta;
	double eI,eO;
	// check if wi ray is in the medium
	bool inMedium = Vector::Dot(normal, wo) > 0.0 ? true : false;
	if (inMedium)
	{
		n = -n;
		eI = m_eta;
		eO = 1.0;
	}
	else
	{
		eI = 1.0;
		eO = m_eta;
	}
	cosTheta = std::sqrt(std::fmax(0.0, 1 - (1 - cosPhi*cosPhi) * (eO*eO / (eI*eI))));
	
	double fresnel = FresnelDielectric(eO, eI, cosTheta, cosPhi);
	//double eBig = std::fmax(eI, eO);
	//double eSmall = std::fmin(eI, eO);
	//double r0 = (eBig - eSmall) / (eBig + eSmall); r0 = r0*r0;
	//double c = (1 - std::fabs(std::fmin(cosPhi,cosTheta)));
	*pdf = 1.0f;
	//double schlick = r0 + (1 - r0)*c*c*c*c*c;
	if (sampler.GetDouble() < fresnel)
	{
		Vector n = Vector::Dot(normal, wo) >= 0 ? normal : -normal;
		*wi = n * (2 * Vector::Dot(wo, n)) - wo;
		return m_color * (1.0 / cosTheta);
	}
	*wi = n*cosTheta - (wo + n*cosPhi) * (eO / eI);
	return m_color * (1.0 / cosTheta);
}
