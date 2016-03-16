#pragma once
#include "Vector.h"
#include "Transform.h"
#include "Point.h"
class Ray;
class Camera
{
public:
	Camera();
	Camera(const Point &position, const Point &focus, const Vector &up, float fieldOfView, float aspect);
	~Camera();
	Ray GenerateRay(float x, float y);
private:
	float m_aspect;
	float m_distance;
	Point m_position;
	Transform m_cameraToWorld;
};

