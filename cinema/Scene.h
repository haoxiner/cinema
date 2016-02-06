#pragma once
#include <vector>
#include "Model.h"
class Ray;
class Intersection;

class Scene
{
public:
	Scene();
	~Scene();
	float Intersect(const Ray &ray, Intersection &intersection);
private:
	std::vector<Model> models;
};

