#pragma once
#include "Color.h"

class Ray;
class Scene;
class Sampler;
class Renderer
{
public:
	Renderer(unsigned int bounceDepth,unsigned int samplesPerPixel);
	~Renderer();
	Color Render(const Ray &cameraRay, const Scene &scene, Sampler &sampler);
	unsigned int samplesPerPixel;
private:
	unsigned int m_bounceDepth;
};

