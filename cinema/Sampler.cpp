#include "Sampler.h"
#include <functional>

Sampler::Sampler(unsigned int seed) :m_engine(seed), m_distribution(0.0, 1.0)
{
	
}

double Sampler::GetDouble()
{
	return m_distribution(m_engine);
}
