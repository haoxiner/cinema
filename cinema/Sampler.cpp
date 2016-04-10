#include "Sampler.h"
#include <random>
#include <ctime>
Sampler::Sampler()
{
	srand(time(nullptr));
}

double Sampler::GetDouble() const
{
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}
