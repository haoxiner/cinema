#include "Sampler.h"
#include <random>
#include <ctime>
Sampler::Sampler()
{
	srand(time(nullptr));
}

float Sampler::GetFloat() const
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}
