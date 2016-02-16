#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"

Scene::Scene()
{
	Triangle *t = new Triangle();
	t->p0 = Point(100, 100, 10);
	t->p1 = Point(100, -100, 10);
	t->p2 = Point(-100, -100, 10);
	models.push_back(t);
}


Scene::~Scene()
{
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		delete *modelIter;
	}
}

bool Scene::Intersect(const Ray &ray, Intersection &intersection)
{
	float t = std::numeric_limits<float>::infinity();
	float tHit = std::numeric_limits<float>::infinity();
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		if ((*modelIter)->Intersect(ray, &tHit) && tHit - t < 0.001f)
		{
			t = tHit;
		}
	}
	if (t < std::numeric_limits<float>::infinity())
	{
		return true;
	}
	else
	{
		return false;
	}
}