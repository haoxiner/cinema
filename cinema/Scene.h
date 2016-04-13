#pragma once
#include <vector>
class Ray;
class Intersection;
class Model;
class Geometry;
class Scene
{
public:
	Scene();
	~Scene();
	bool Intersect(const Ray &ray, Intersection &intersection)const;
	void AddModel(Model *model);
private:
	std::vector<Model*> models;
	std::vector<Geometry*> geometries;
};

