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
	/*Triangle *t = new Triangle();
	t->p0 = Point(15, 15, -10);
	t->p1 = Point(15, -15, -10);
	t->p2 = Point(-15, -15, -10);
	Model *model = new Model;
	model->geometry = t;
	models.push_back(model);*/

	Sphere *s = new Sphere(Point(-10, 0, -5), 5);
	Model *model1 = new Model();
	model1->geometry = s;
	model1->bsdf = new SpecularReflection(Color(0,0,0));
	model1->emit = 1.0;
	models.push_back(model1);

	Sphere *s2(new Sphere(Point(10, 0, -5), 8));
	Model *m2(new Model);
	m2->geometry = s2;
	m2->bsdf = new DiffuseReflection(Color(0.5, 0, 0));
	models.push_back(m2);

	TriangleMesh *mesh = new TriangleMesh;
	Model *model = new Model;
	mesh->vertices.push_back(Point(-15, 15, -5));
	mesh->vertices.push_back(Point(-20, -10, -5));
	mesh->vertices.push_back(Point(5, -10, -5));
	mesh->vertices.push_back(Point(-30, 30, -15));

	mesh->indices.push_back(0); mesh->indices.push_back(0); mesh->indices.push_back(0);
	mesh->indices.push_back(1); mesh->indices.push_back(0); mesh->indices.push_back(0);
	mesh->indices.push_back(2); mesh->indices.push_back(0); mesh->indices.push_back(0);
	mesh->indices.push_back(0); mesh->indices.push_back(0); mesh->indices.push_back(0);
	mesh->indices.push_back(2); mesh->indices.push_back(0); mesh->indices.push_back(0);
	mesh->indices.push_back(3); mesh->indices.push_back(0); mesh->indices.push_back(0);

	mesh->normals.push_back(Vector(0, 0, 1));
	model->bsdf = new DiffuseReflection(Color(1, 1, 1));
	Triangle triangle;
	triangle.mesh = mesh;
	triangle.v = &mesh->indices[0];
	mesh->triangles.push_back(triangle);
	model->geometry = &mesh->triangles[0];
	model->emit = Color(0.5, 0, 0);
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
	double t = std::numeric_limits<double>::infinity();
	// current hit t
	double tHit = std::numeric_limits<double>::infinity();
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
	if (t < std::numeric_limits<double>::infinity())
	{
		intersection.point = ray.GetPoint(t);
		intersection.normal = intersection.geometry->GetNormal(intersection.point, intersection.u1, intersection.u2).Normalize();
		return true;
	}
	else
	{
		return false;
	}
}