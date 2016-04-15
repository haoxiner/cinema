#include "Sampler.h"


Sampler::Sampler():dis(std::uniform_real_distribution<double>(0.0,1.0))
{
}

void Sampler::Seed(unsigned int s)
{
	random.seed(s);
}

double Sampler::GetDouble() const
{
	return dis(random);
	//return 0.5;
}
