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
#include <process.h>
#include <Windows.h>
#include <ctime>

static Image *image;
static Camera *camera;
static Renderer *renderer;
static Scene *scene;
// samplesPerPixel
static int spp;
// stratified sampling: step in one pixel
static double step;
// half resolution
static double halfwidth;
static double halfHeight;
// statistics shared by threads
long columnCount = 0;

void Initialize();
void DispatchTask(const int numOfThread);
void WriteToFile(const char * filepath);
unsigned __stdcall renderTask(void *p);

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
	{
		fprintf(stderr, "Usage: cinema scene_file_name.xml [number of thread]");
		return 0; 
	}
	int numOfThread = 2;
	if (argc == 3)
	{
		int threads = atoi(argv[2]);
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		int numOfProcessors = si.dwNumberOfProcessors;
		numOfThread = (threads > numOfProcessors || threads < 1) ? numOfProcessors : (threads);
	}
	fprintf(stderr, "Threads: %d\n", numOfThread);
	// parse scene.xml
	Parser parser;
	parser.Parse(argv[1]);
	image = parser.GetImage();
	camera = parser.GetCamera();
	renderer = parser.GetRenderer();
	scene = parser.GetScene();
	// render
	Initialize();
	DispatchTask(numOfThread);
	WriteToFile("E:\\render.bmp");
	return 0;
}

unsigned __stdcall renderTask(void *p)
{
	int *column = (int*)p;
	int start = column[0];
	int end = column[1];
	// random generator is not thread-safe
	Sampler sampler(start);
	for (int i = start; i < end; ++i)
	{
		for (int j = 0; j < static_cast<int>(image->yResolution); ++j)
		{
			Color pixel;
			// stratified sampling
			for (int k = 0; k < spp; ++k)
			{
				double subI = i + k*step + sampler.GetDouble()*step;
				double subJ = j + k*step + sampler.GetDouble()*step;
				double x = (subI - halfwidth) / halfwidth;
				double y = (subJ - halfHeight) / halfHeight;
				Ray ray = camera->GenerateRay(x, y);
				pixel += renderer->Render(ray, *scene, sampler);
			}
			pixel *= step;
			image->SetColor(i, j, pixel);
		}
		// update progress
		InterlockedIncrement(&columnCount);
		fprintf(stderr, "\rRendering: %.2f %%", columnCount / static_cast<float>(image->xResolution) * 100);
		fflush(stderr);
	}
	return 0;
}

void Initialize()
{
	spp = static_cast<int>(renderer->samplesPerPixel);
	step = 1.0 / spp;
	halfwidth = static_cast<double>(image->xResolution) / 2.0;
	halfHeight = static_cast<double>(image->yResolution) / 2.0;
}

void DispatchTask(const int numOfThread)
{
	// HANDLE
	uintptr_t *thd = new uintptr_t[numOfThread];
	// thread id
	unsigned *tid = new unsigned[numOfThread];
	// column per thread
	int taskStep = static_cast<int>(image->xResolution) / numOfThread;
	// start time (second)
	time_t t1 = time(nullptr);
	// argument[0]: start column , argument[1]: next start column
	int *arguments = new int[numOfThread * 2];

	fprintf(stderr, "\rRendering: 0.0 %%");
	fflush(stderr);
	// dispatch
	int last = numOfThread - 1;
	for (int i = 0; i < last; ++i)
	{
		arguments[i * 2] = i*taskStep;
		arguments[i * 2 + 1] = (i + 1)*taskStep;
		thd[i] = _beginthreadex(nullptr, 0, renderTask, (void*)(&arguments[i*2]), 0, &tid[i]);
	}
	arguments[last * 2] = last*taskStep;
	arguments[last * 2 + 1] = static_cast<int>(image->xResolution);
	thd[last] = _beginthreadex(nullptr, 0, renderTask, (void*)(&arguments[last * 2]), 0, &tid[last]);

	for (size_t i = 0; i < numOfThread; i++)
	{
		WaitForSingleObject((HANDLE)thd[i], INFINITE);
		CloseHandle((HANDLE)thd[i]);
	}
	time_t t2 = time(nullptr);
	fprintf(stderr, "\rRendering: %.2f %%", columnCount / static_cast<float>(image->xResolution) * 100);
	fprintf(stderr, "\nTime used: %us\n", static_cast<unsigned int>(t2 - t1));
	fflush(stderr);
}

void WriteToFile(const char * filepath)
{
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
	image->WriteToFile(filepath);
}