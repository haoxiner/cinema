#include "Camera.h"
#include "Ray.h"
#include <cmath>

Camera::Camera()
{
}


Camera::~Camera()
{

}
Camera::Camera(float aspect):m_aspect(aspect)
{

}
Camera::Camera(const Vector & gaze, const Vector & up, const Point & position, float fieldOfView, float aspect):
	m_position(position),m_aspect(aspect),m_distance(1.0f / std::tanf(fieldOfView / 2.0f))
{
	Vector egaze = Vector::Normalize(gaze);
	Vector eright = Vector::Normalize(Vector::Cross(gaze, up));
	Vector eup = Vector::Cross(eright, egaze);
	m_cameraToWorld.SetMatrix(
		eright.x, eup.x, egaze.x, position.x,
		eright.y, eup.y, egaze.y, position.y,
		eright.z, eup.z, egaze.z, position.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}
Ray Camera::GenerateRay(float x, float y)
{
	Vector direction(x*m_aspect, y, m_distance);
	return Ray(m_position, m_cameraToWorld(direction));
}