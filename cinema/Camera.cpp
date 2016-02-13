#include "Camera.h"
#include "Ray.h"


Camera::Camera()
{
}


Camera::~Camera()
{

}
Camera::Camera(float aspect):m_aspect(aspect)
{

}
Ray Camera::GenerateRay(float x, float y)
{
	Vector direction(x*m_aspect, y, m_distance);
	return Ray(m_position, direction);
}