#pragma once
#include <vector>
class Ray;
class Intersection;
class Model;

class Scene
{
public:
	Scene();
	~Scene();
	bool Intersect(const Ray &ray, Intersection &intersection)const;
private:
	std::vector<Model*> models;
};

