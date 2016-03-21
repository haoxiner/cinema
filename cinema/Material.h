#pragma once
#include <vector>
class BSDF;
class Material
{
public:
	Material();
	~Material();
public:
	std::vector<BSDF*> bxdfs;
};

