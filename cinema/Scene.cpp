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
#include "KDTree.h"

Scene::Scene() :Environment(Color::BLACK)
{
}


Scene::~Scene()
{
	for (auto modelIter = m_models.begin(); modelIter != m_models.end(); ++modelIter)
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
	auto geometries = kdtree->Intersect(ray);
	if (geometries == nullptr)
	{
		return false;
	}
	for (auto geometry : *geometries/*m_geometries*/)
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
	model->GetGeometries(&m_geometries);
	m_models.push_back(model);
}

void Scene::Buildkdtree()
{
	kdtree = KDTree::Build(m_geometries);
}
