#pragma once
double FresnelDielectric(const double etaT, const double etaI, const double cosI, const double cosT)
{
	double r1 = (etaT*cosI - etaI*cosT) / (etaT*cosI + etaI*cosT);
	double r2 = (etaI*cosI - etaT*cosT) / (etaI*cosI + etaT*cosT);
	return 0.5*(r1*r1 + r2*r2);
}