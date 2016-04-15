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
#include <process.h>
#include <Windows.h>

void TestRender();
int main(int argc, char *argv[])
{
	TestRender();
	return 0;
}

Image *image;
Camera *camera;
Renderer *renderer;
Scene *scene;
int spp;
double step;
int halfwidth;
int halfHeight;
Sampler sampler;

unsigned __stdcall renderTask(void *p)
{
	int *segment = (int*)p;
	int start = segment[0];
	int end = segment[1];
	
	for (int i = start; i < end; ++i)
	{
		for (int j = 0; j < static_cast<int>(image->yResolution); ++j)
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
	}
	return 0;
}

void TestRender()
{
	Parser parser;
	parser.Parse("scene02.xml");
	image = parser.GetImage();
	camera = parser.GetCamera();
	renderer = parser.GetRenderer();
	scene = parser.GetScene();
	renderer->SetSampler(&sampler);
	spp = static_cast<int>(renderer->m_samplesPerPixel);
	step = 1.0 / spp;
	halfwidth = static_cast<int>(image->xResolution) / 2;
	halfHeight = static_cast<int>(image->yResolution) / 2;

	int numOfThread = 8;
	unsigned long *thd = new unsigned long[numOfThread];
	unsigned *tid = new unsigned[numOfThread];
	int taskStep = static_cast<int>(image->xResolution) / numOfThread;

	int *segment = new int[numOfThread * 3];
	for (int i = 0; i < numOfThread; ++i)
	{
		if ((i + 1)*taskStep >= static_cast<int>(image->xResolution) - 1)
		{
			segment[i * 3] = i*taskStep;
			segment[i * 3 + 1] = static_cast<int>(image->xResolution);
			segment[i * 3 + 2] = i;
			thd[i] = _beginthreadex(nullptr, 0, renderTask, (void*)(&segment[i*2]), 0, &tid[i]);
			break;
		}
		segment[i * 3] = i*taskStep;
		segment[i * 3 + 1] = (i + 1)*taskStep;
		segment[i * 3 + 2] = i;
		thd[i] = _beginthreadex(nullptr, 0, renderTask, (void*)(&segment[i*2]), 0, &tid[i]);
	}
	
	for (size_t i = 0; i < numOfThread; i++)
	{
		WaitForSingleObject((HANDLE)thd[i], INFINITE);
	}

	for (size_t i = 0; i < numOfThread; ++i)
	{
		CloseHandle((HANDLE)thd[i]);
	}
	for (int i = 0; i < static_cast<int>(image->xResolution); i++)
	{
		image->SetColor(i, 0, Color::WHITE);
		image->SetColor(i, image->yResolution - 1, Color::WHITE);
	}
	for (int i = 0; i < static_cast<int>(image->yResolution); i++)
	{
		image->SetColor(0, i, Color::WHITE);
		image->SetColor(image->xResolution - 1, i, Color::WHITE);
	}
	image->WriteToFile("E:/result.bmp");
}