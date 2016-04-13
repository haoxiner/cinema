#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Geometry.h"
#include "Model.h"
#include "SpecularReflection.h"
#include "DiffuseReflection.h"
#include "TriangleMesh.h"
Scene::Scene()
{
}


Scene::~Scene()
{
	for (auto modelIter = models.begin(); modelIter != models.end(); ++modelIter)
	{
		delete *modelIter;
	}
}

bool Scene::Intersect(const Ray &ray, Intersection &intersection)const
{
	// final t
	double t = std::numeric_limits<double>::infinity();
	// current hit t
	double tHit = std::numeric_limits<double>::infinity();
	Intersection currentIntersection;
	// check intersection
	for (auto geometry : geometries)
	{
		if (geometry->Intersect(ray, &tHit, &currentIntersection) && tHit < t)
		{
			intersection = currentIntersection;
			intersection.model = geometry->model;
			t = tHit;
		}
	}
	// if hit, shade
	if (t < std::numeric_limits<double>::infinity())
	{
		intersection.point = ray.GetPoint(t);
		intersection.normal = intersection.geometry->GetNormal(intersection).Normalize();
		return true;
	}
	else
	{
		return false;
	}
}

void Scene::AddModel(Model * model)
{
	model->GetGeometries(&geometries);
	models.push_back(model);
}
