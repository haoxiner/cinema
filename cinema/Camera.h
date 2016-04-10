#pragma once
#include "Vector.h"
#include "Transform.h"
#include "Point.h"
class Ray;
class Camera
{
public:
	Camera();
	Camera(const Point &position, const Point &focus, const Vector &up, double fieldOfView, double aspect);
	~Camera();
	Ray GenerateRay(double x, double y);
private:
	double m_aspect;
	double m_distance;
	Point m_position;
	Transform m_cameraToWorld;
};

