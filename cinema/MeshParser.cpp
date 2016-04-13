#include "MeshParser.h"
#include "Model.h"
#include "TriangleMesh.h"
#include <fstream>
#include <sstream>


MeshParser::MeshParser()
{
}


MeshParser::~MeshParser()
{
}

void MeshParser::Parse(Model * model, const char * filepath)
{
	std::ifstream in(filepath);
	std::ostringstream oss;
	oss << in.rdbuf();
	buffer = oss.str();
	in.close();
	index = 0;
	TriangleMesh *mesh = new TriangleMesh;
	model->AddGeometry(mesh);
	while (index < buffer.length())
	{
		if (buffer[index] == 'v')
		{
			++index;
			if (buffer[index] == 't')
			{
				++index;
				SkipSpace();
				double u = ParseDouble();
				SkipSpace();
				double v = ParseDouble();
				mesh->uvs.push_back(static_cast<float>(u));
				mesh->uvs.push_back(static_cast<float>(v));
			}
			else if (buffer[index] == 'n')
			{
				++index;
				Vector n;
				SkipSpace();
				ParseTripleDouble(&n.x, &n.y, &n.z);
				mesh->normals.push_back(n);
			}
			else
			{
				Point p;
				SkipSpace();
				ParseTripleDouble(&p.x, &p.y, &p.z);
				mesh->vertices.push_back(p);
			}
		}
		else if (buffer[index] == 'f')
		{
			++index;
			SkipSpace();
			for (size_t i = 0; i < 3; ++i)
			{
				while (!isdigit(buffer[index]))
				{
					++index;
				}
				mesh->indices.push_back(ParseUnsignedInteger() - 1);
				++index;
				mesh->indices.push_back(ParseUnsignedInteger() - 1);
				++index;
				mesh->indices.push_back(ParseUnsignedInteger() - 1);
			}
		}
		NextLine();
	}
	mesh->MakeTriangles();
}

void MeshParser::SkipSpace()
{
	while (isspace(buffer[index]))
	{
		++index;
	}
}

unsigned int MeshParser::ParseUnsignedInteger()
{
	unsigned int ret = atoi(&buffer[index]);
	while (isdigit(buffer[index]))
	{
		++index;
	}
	return ret;
}

double MeshParser::ParseDouble()
{
	double ret = atof(&buffer[index]);
	while (!isspace(buffer[index]))
	{
		++index;
	}
	return ret;
}

void MeshParser::ParseTripleDouble(double * x, double * y, double * z)
{
	*x = ParseDouble();
	SkipSpace();
	*y = ParseDouble();
	SkipSpace();
	*z = ParseDouble();
}

void MeshParser::NextLine()
{
	while (buffer[index] != '\n')
	{
		++index;
	}
	if (buffer[index] == '\n')
	{
		++index;
	}
}
