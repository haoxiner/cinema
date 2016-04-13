#include "Model.h"
#include "Intersection.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::GetGeometries(std::vector<Geometry*> *geometries)
{
	for (auto geometry : m_geometries)
	{
		geometry->Extract(geometries);
	}
	
}

void Model::AddGeometry(Geometry * geometry)
{
	geometry->model = this;
	m_geometries.push_back(geometry);
}


