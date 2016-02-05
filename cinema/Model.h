#pragma once
class Ray;
class Model
{
public:
	Model();
	virtual ~Model() = 0;
	virtual float Intersect(const Ray &ray) = 0;
};

