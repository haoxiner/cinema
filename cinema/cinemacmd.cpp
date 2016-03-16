#include "Vector.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "Color.h"
#include "Scene.h"
#include "Intersection.h"
#include <vector>
#include <iostream>
#include <random>
#include <limits>

#include <fstream>

Scene scene;

Color Render(const Ray &ray,unsigned int depth)
{
	if (depth == 0)
	{
		return Color::WHITE;
	}
	Intersection intersection;
	bool hit = scene.Intersect(ray,intersection);
	if (hit)
	{
		return intersection.color;
	}
	else
	{
		return Color::BLACK;
	}
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
	float a = std::numeric_limits<float>::infinity();
	float b = std::numeric_limits<float>::infinity();
	float c = 1e20f;
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
			Ray ray = camera.GenerateRay(static_cast<float>(i-400) / 400.0f, static_cast<float>(j-300) / 300.0f);
			Color color = Render(ray, 1);
			image.SetColor(i, j, color);
		}
	}
	image.WriteToFile("C:/Resource/result.bmp");
}