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
	void SetSampler(Sampler *sampler);
	unsigned int m_samplesPerPixel;
private:
	Sampler *m_sampler;
	unsigned int m_bounceDepth;
};

