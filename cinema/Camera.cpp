#include "Camera.h"
#include "Ray.h"
#include <cmath>

#define PI 3.14159265f

Camera::Camera()
{
}
Camera::~Camera()
{

}

Camera::Camera(const Point & position, const Point & focus, const Vector & up, 
	double fieldOfView, double aspect):
	m_position(position), m_aspect(aspect), m_distance(1.0f / std::tan(fieldOfView / 180.0f*PI / 2.0f))
{
	Vector egaze = -Vector::Normalize(focus - position);
	Vector eright = Vector::Normalize(Vector::Cross(Vector::Normalize(up), egaze));
	Vector eup = Vector::Cross(egaze, eright);

	m_cameraToWorld.SetMatrix(
		eright.x, eup.x, egaze.x, position.x,
		eright.y, eup.y, egaze.y, position.y,
		eright.z, eup.z, egaze.z, position.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Ray Camera::GenerateRay(double x, double y)
{
	Vector direction(x*m_aspect, y, -m_distance);
	return Ray(m_position, m_cameraToWorld(direction));
}