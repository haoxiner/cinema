#include "Renderer.h"
#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"
#include "Model.h"
#include "BSDF.h"
#include "Sampler.h"
#include <cmath>

Renderer::Renderer(unsigned int bounceDepth, unsigned int samplesPerPixel):m_bounceDepth(bounceDepth),
samplesPerPixel(samplesPerPixel)
{
}

Renderer::~Renderer()
{
}

/*
 * monte carlo path tracing
 * path bsdfs are multiplied and stored in pathColor
 */
Color Renderer::Render(const Ray & cameraRay, const Scene &scene,Sampler &sampler)
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
			color += pathColor * scene.Environment;
			break;
		}
		if (intersection.model->emit != Color::BLACK)
		{
			color += pathColor*(Vector::Dot(intersection.normal, wo) > 0 ? intersection.model->emit : 0);
			break;
		}
		/*
		 * some bsdf and related pdf have been simplified when calling bsdf->f
		 * so bsdf and pdf may not be the 'correct' value
		 */
		double pdf;
		Color bsdf = intersection.model->bsdf->f(intersection.normal, wo.Normalize(), &wi, &pdf, sampler);
		double wiDotN = Vector::Dot(intersection.normal, wi);
		pathColor *= (bsdf*(std::fabs(wiDotN) / pdf));
		if (bounces == m_bounceDepth)
		{
			double p = std::fmax(pathColor.r, std::fmax(pathColor.g, pathColor.b));
			if (sampler.GetDouble() < p)
			{
				pathColor *= (1.0 / p);
			}
			else
			{
				break;
			}
		}
		ray.o = intersection.point;
		ray.d = wi;
		wo = -wi;
	}
	return color;
}