#pragma once
class Ray;
class Camera
{
public:
	Camera();
	Camera(float aspect);
	~Camera();
	Ray GenerateRay(float x, float y);
};

