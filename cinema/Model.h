#pragma once
class Ray;
class Model
{
public:
	Model();
	virtual ~Model() = 0;
	virtual bool Intersect(const Ray &ray, float *t) = 0;
};

