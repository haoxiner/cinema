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
	Scene *scene = new Scene;
	for (int i = 0; i < 800; ++i)
	{
		for (int j = 0; j < 600; ++j)
		{
			Ray ray = camera->GenerateRay(static_cast<double>(i-400) / 400.0, static_cast<double>(j-300) / 300.0);
			Color color = renderer->Render(ray,*scene);
			image->SetColor(i, j, color);
		}
	}
	image->WriteToFile("E:/result.bmp");
}