#include "Scene.h"
#include "Ray.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

float Scene::Intersect(const Ray &ray, Intersection &intersection)
{
	float t = 0.0f;
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		float tHit = modelIter->Intersect(ray);
		if (tHit - t < 0.001f)
		{
			t = tHit;
		}
	}
	return t;
}