#pragma once
#include <vector>
#include "Color.h"
class Ray;
class Intersection;
class Model;
class Geometry;
class KDTree;
class Scene
{
public:
	Scene();
	~Scene();
	bool Intersect(const Ray &ray, Intersection &intersection)const;
	void AddModel(Model *model);
	void Buildkdtree();
	Color Environment;
private:
	std::vector<Model*> m_models;
	std::vector<Geometry*> m_geometries;
	KDTree * kdtree;
};

