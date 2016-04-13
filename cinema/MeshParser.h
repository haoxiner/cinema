#pragma once
#include <string>
class Model;
class MeshParser
{
public:
	MeshParser();
	~MeshParser();
	void Parse(Model *model, const char* filepath);
	void SkipSpace();
	unsigned int ParseUnsignedInteger();
	double ParseDouble();
	void ParseTripleDouble(double *x, double *y, double *z);
	void NextLine();
private:
	unsigned int index;
	std::string buffer;
};

