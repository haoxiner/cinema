#pragma once
#include <random>
class Sampler
{
public:
	Sampler();
	void Seed(unsigned int s);
	double GetDouble()const;
private:
	std::default_random_engine random;
	std::uniform_real_distribution<double> dis;
};