#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersection.h"

Scene::Scene()
{
	/*Triangle *t = new Triangle();
	t->p0 = Point(15, 15, 25);
	t->p1 = Point(15, -15, 25);
	t->p2 = Point(-15, -15, 25);
	models.push_back(t);*/
	Sphere *s = new Sphere(Point(0, 0, 15), 10);
	models.push_back(s);
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
		if ((*modelIter)->Intersect(ray, &tHit) && tHit < t)
		{
			t = tHit;
		}
	}
	if (t < std::numeric_limits<float>::infinity())
	{
		intersection.point = ray.GetPoint(t);
		intersection.normal = intersection.point - Point(0, 0, 15);
		intersection.normal = Vector::Normalize(intersection.normal);

		intersection.color = Vector::Dot(intersection.normal, Vector::Normalize(Vector(1, 1, -1)));

		//intersection.normal = intersection.normal*0.5f;
		//intersection.color = Color(intersection.normal.x+0.5f,intersection.normal.y + 0.5f,intersection.normal.z + 0.5f);
		return true;
	}
	else
	{
		return false;
	}
}