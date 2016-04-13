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
#include "Parser.h"
#include "Renderer.h"
#include <vector>
#include <iostream>
#include <random>
#include <limits>

void TestRender();
int main(int argc, char *argv[])
{
	TestRender();
	return 0;
}

void TestRender()
{
	Parser parser;
	parser.Parse("scene01.xml");
	Image *image = parser.GetImage();
	Camera *camera = parser.GetCamera();
	Renderer *renderer = parser.GetRenderer();
	Scene *scene = parser.GetScene();
	Sampler sampler;
	renderer->SetSampler(&sampler);
	int spp = static_cast<int>(renderer->m_samplesPerPixel);
	double step = 1.0 / spp;

	auto halfwidth = image->xResolution / 2;
	auto halfHeight = image->yResolution / 2;
	for (int i = 0; i < image->xResolution; ++i)
	{
		for (int j = 0; j < image->yResolution; ++j)
		{
			Color pixel;
			for (int k = 0; k < spp; ++k)
			{
				double subI = i + k*step + sampler.GetDouble()*step;
				double subJ = j + k*step + sampler.GetDouble()*step;
				double x = static_cast<double>(subI - static_cast<double>(halfwidth)) / static_cast<double>(halfwidth);
				double y = static_cast<double>(subJ - static_cast<double>(halfHeight)) / static_cast<double>(halfHeight);
				Ray ray = camera->GenerateRay(x, y);
				pixel += renderer->Render(ray, *scene) * step;
			}
			image->SetColor(i, j, pixel);
		}
		fprintf(stderr, "%d\n", i);
		fflush(stderr);
	}
	image->WriteToFile("E:/result.bmp");
}