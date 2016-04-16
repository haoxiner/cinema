#pragma once
#include <random>
class Sampler
{
public:
	Sampler(unsigned int seed);
	double GetDouble();
private:
	std::default_random_engine m_engine;
	std::uniform_real_distribution<double> m_distribution;
};