#pragma once
#include "Vector.h"
#include "Transform.h"
class Ray;
class Camera
{
public:
	Camera();
	Camera(float aspect);
	~Camera();
	Ray GenerateRay(float x, float y);
private:
	float m_aspect;
	float m_distance;
	Vector m_position;
	Transform m_cameraToWorld;
};

