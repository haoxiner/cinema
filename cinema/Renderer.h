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
	Color Render(const Ray &cameraRay, const Scene &scene);
private:
	Sampler *sampler;
	unsigned int m_bounceDepth;
	unsigned int m_samplesPerPixel;
};

