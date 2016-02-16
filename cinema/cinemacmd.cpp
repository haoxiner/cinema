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

Scene scene;

Color Render(const Ray &ray,unsigned int depth)
{
	static unsigned int cnt = 0;
	if (depth == 0)
	{
		return Color::WHITE;
	}
	Intersection intersection;
	bool hit = scene.Intersect(ray,intersection);
	if (hit)
	{
		++cnt;
		std::cerr << cnt << " ";
		return Color::WHITE;
	}
	else
	{
		return Color::BLACK;
	}
}

void ShowImage(Image *img);

void TestRender();
void TestBMP();
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
void TestBMP()
{
	int i = 0;
	int j = i + 1;
	std::cerr << "1" << std::endl;
	Image img(800, 600);
	std::cerr << "2" << std::endl;
	srand(0);
	float max = static_cast<float>(RAND_MAX);
	for (size_t i = 0; i < 800; ++i)
	{
		for (size_t j = 0; j < 600; ++j)
		{
			Color c(rand() / max, rand() / max, rand() / max);
			img.SetColor(i, j, c);
		}
	}

	img.WriteToFile("D:\\test.bmp");
	std::cerr << "3" << std::endl;
}
void TestRender()
{
	Image image(800, 600);
	Camera camera(Vector(0, 0, 1), Vector(0, 1, 0), Point(0, 0, 0), 90.0f, 4.0f / 3.0f);
	for (size_t i = 0; i < 800; ++i)
	{
		for (size_t j = 0; j < 600; ++j)
		{
			Ray ray = camera.GenerateRay(static_cast<float>(i) / 800.0f, static_cast<float>(j) / 600.0f);
			Color color = Render(ray, 1);
			image.SetColor(i, j, color);
		}
	}
	image.WriteToFile("D:\\test.bmp");
}