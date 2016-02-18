#pragma once
#include "Model.h"
#include <vector>
class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();
	std::vector<Model*> Load(const char *path);
};

