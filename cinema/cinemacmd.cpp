#include "Vector.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "Color.h"
#include "Scene.h"
#include "Intersection.h"
#include <vector>

Scene scene;

Color Render(const Ray &ray,unsigned int depth)
{
	if (depth == 0)
	{
		return;
	}
	Intersection intersection;
	bool hit = scene.Intersect(ray,intersection);
	if (hit)
	{
		return Color::WHITE;
	}
	else
	{
		return Color::BLACK;
	}
}

void ShowImage(Image *img);

int main(int argc, char *argv[])
{
	Image image(800,600);
	Camera camera(4.0f/3.0f);
	for (size_t i = 0; i < 800; ++i)
	{
		for (size_t j = 0; j < 600; ++j)
		{
			Ray ray = camera.GenerateRay(static_cast<float>(i), static_cast<float>(j));
			Color color = Render(ray, 1);
			image.SetColor(i, j, color);
		}
	}
	WriteImage(image);
	return 0;
}

void WriteImage(Image &img)
{

}