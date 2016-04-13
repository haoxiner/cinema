#include "Renderer.h"
#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"
#include "Model.h"
#include "BSDF.h"
#include "Sampler.h"
#include <cmath>

Renderer::Renderer(unsigned int bounceDepth, unsigned int samplesPerPixel):m_sampler(nullptr),m_bounceDepth(bounceDepth),
m_samplesPerPixel(samplesPerPixel)
{
}

Renderer::~Renderer()
{
}

Color Renderer::Render(const Ray & cameraRay, const Scene &scene)
{
	Color color = Color::BLACK;
	Color pathColor = Color::WHITE;

	Intersection intersection;
	Vector wi;
	Vector wo(-cameraRay.d);
	Ray ray(cameraRay);

	for (size_t bounces = 0; ; ++bounces)
	{
		if (!scene.Intersect(ray, intersection))
		{
			break;
		}
		color += pathColor*(intersection.model->emit);
		if (intersection.model->emit.r != 0)
		{
			break;
		}
		double pdf;
		if (Vector::Dot(intersection.normal, wo) < 0)
		{
			intersection.normal = -intersection.normal;
		}
		Color brdf = intersection.model->bsdf->f(intersection.normal, wo.Normalize(), &wi, &pdf, *m_sampler);
		double wiDotN = Vector::Dot(intersection.normal, wi.Normalize());
		pathColor *= (brdf*std::abs(wiDotN));
		if (bounces < m_bounceDepth)
		{
			ray.o = intersection.point;
			ray.d = wi;
			wo = -wi;
		}
		else
		{
			break;
		}
	}
	return color;
}

void Renderer::SetSampler(Sampler * sampler)
{
	m_sampler = sampler;
}
