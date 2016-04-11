#include "Vector.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "Color.h"
#include "Scene.h"
#include "Intersection.h"
#include "BSDF.h"
#include "Model.h"
#include "Sampler.h"
#include <vector>
#include <iostream>
#include <random>
#include <limits>

#include <fstream>

Scene scene;
Sampler sampler;

Color Render(const Ray &cameraRay)
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
		Color brdf = intersection.model->bsdf->f(intersection.normal, wo.Normalize(), &wi, &pdf, &sampler);
		pathColor *= (brdf*std::fmax(0.0, Vector::Dot(intersection.normal, wi.Normalize())));
		if (bounces < 5)
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

void TestRender();
void Test();
int main(int argc, char *argv[])
{
	
	TestRender();
	return 0;
}
void Test()
{
	double a = std::numeric_limits<double>::infinity();
	double b = std::numeric_limits<double>::infinity();
	double c = 1e20f;
	std::cerr << (b < a) << std::endl;
	std::cerr << (c < a) << std::endl;
}
void TestRender()
{
	Image image(800, 600);
	Camera camera(Point(0, 0, 15), Point(0, 0, 0), Vector(0, 1, 0), 90.0f, 4.0f / 3.0f);
	
	for (int i = 0; i < 800; ++i)
	{
		for (int j = 0; j < 600; ++j)
		{
			Ray ray = camera.GenerateRay(static_cast<double>(i-400) / 400.0, static_cast<double>(j-300) / 300.0);
			Color color = Render(ray);
			image.SetColor(i, j, color);
		}
	}
	image.WriteToFile("E:/result.bmp");
}