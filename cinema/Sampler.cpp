#include "Sampler.h"
#include <random>
#include <ctime>
Sampler::Sampler()
{
}

double Sampler::GetDouble() const
{
	static std::default_random_engine random(time(nullptr));
	static std::uniform_real_distribution<double> dis(0.0, 1.0);
	return dis(random);
}
