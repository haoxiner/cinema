#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Geometry.h"
#include "Model.h"

Scene::Scene()
{
	/*Triangle *t = new Triangle();
	t->p0 = Point(15, 15, -10);
	t->p1 = Point(15, -15, -10);
	t->p2 = Point(-15, -15, -10);
	Model *model = new Model;
	model->geometry = t;
	models.push_back(model);*/
	Sphere *s = new Sphere(Point(0, 0, 0), 10);
	Model *model = new Model();
	model->geometry = s;
	models.push_back(model);
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
	// check intersection
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		if ((*modelIter)->Intersect(ray, &tHit, &intersection) && tHit < t)
		{
			intersection.model = *modelIter;
			t = tHit;
		}
	}
	// if hit, shade
	if (t < std::numeric_limits<float>::infinity())
	{
		intersection.point = ray.GetPoint(t);
		intersection.normal = intersection.point - Point(0,0,0);
		intersection.normal = Vector::Normalize(intersection.normal);

		intersection.color = Vector::Dot(intersection.normal, Vector::Normalize(Point(0, 0, 20) - intersection.point));
		//intersection.color = Color::WHITE;
		return true;
	}
	else
	{
		return false;
	}
}