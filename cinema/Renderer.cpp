#include "Renderer.h"
#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"
#include "Model.h"
#include "BSDF.h"
#include "Sampler.h"
#include <cmath>

Renderer::Renderer(unsigned int bounceDepth, unsigned int samplesPerPixel):sampler(new Sampler),m_bounceDepth(5),
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
		color += pathColor*intersection.model->emit;
		double pdf;
		Color brdf = intersection.model->bsdf->f(intersection.normal, wo.Normalize(), &wi, &pdf, *sampler);
		pathColor *= (brdf*std::abs(Vector::Dot(intersection.normal, wi.Normalize())));
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
