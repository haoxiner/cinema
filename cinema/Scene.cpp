#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Geometry.h"
#include "Model.h"
#include "SpecularReflection.h"
Scene::Scene()
{
	/*Triangle *t = new Triangle();
	t->p0 = Point(15, 15, -10);
	t->p1 = Point(15, -15, -10);
	t->p2 = Point(-15, -15, -10);
	Model *model = new Model;
	model->geometry = t;
	models.push_back(model);*/

	Sphere *s = new Sphere(Point(-10, 0, -5), 8);
	Model *model = new Model();
	model->geometry = s;
	model->bsdf = new SpecularReflection(Color(0.3f, 0.0f, 0.0f));
	models.push_back(model);

	Sphere *s2(new Sphere(Point(10, 0, -5), 8));
	Model *m2(new Model);
	m2->geometry = s2;
	m2->bsdf = new SpecularReflection(Color(0.0f, 0.0f, 0.3f));
	models.push_back(m2);
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
	// final t
	float t = std::numeric_limits<float>::infinity();
	// current hit t
	float tHit = std::numeric_limits<float>::infinity();
	Intersection currentIntersection;
	// check intersection
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		if ((*modelIter)->Intersect(ray, &tHit, &currentIntersection) && tHit < t)
		{
			intersection = currentIntersection;
			t = tHit;
		}
	}
	// if hit, shade
	if (t < std::numeric_limits<float>::infinity())
	{
		return true;
	}
	else
	{
		return false;
	}
}