#include "Parser.h"
#include "Camera.h"
#include "Scene.h"
#include "Image.h"
#include "Renderer.h"
#include "Model.h"
#include "SpecularReflection.h"
#include "DiffuseReflection.h"
#include "MeshParser.h"
#include "Sphere.h"
#include <fstream>
#include <sstream>

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::Parse(const char * filepath)
{
	std::ifstream in(filepath);
	std::ostringstream oss;
	oss << in.rdbuf();
	buffer = oss.str();
	in.close();
	index = 0;
	while (HasNextTag())
	{
		std::string tag = NextTag();
		if (tag == "camera")
		{
			ParseCamera();
		}
		else if (tag == "renderer")
		{
			ParseRenderer();
		}
		else if (tag == "scene")
		{
			ParseScene();
		}
	}
}

Camera * Parser::GetCamera()
{
	return camera;
}

Scene * Parser::GetScene()
{
	return scene;
}

Image * Parser::GetImage()
{
	return image;
}

Renderer * Parser::GetRenderer()
{
	return renderer;
}

bool Parser::HasNextTag()
{
	while (index < buffer.length() && buffer[index] != '<')
	{
		++index;
	}
	if (index >= buffer.length())
	{
		return false;
	}
	++index;
	return true;
}

std::string Parser::NextTag()
{
	int begin = index;
	while (buffer[index] != '>')
	{
		++index;
	}
	std::string tag(&buffer[begin], &buffer[index]);
	++index;
	return tag;
}

void Parser::SkipSpace()
{
	while (index < buffer.length() && isspace(buffer[index]))
	{
		++index;
	}
}

double Parser::ParseDouble()
{
	int begin = index;
	while (buffer[index] != '<' && buffer[index] != ',' && !isspace(buffer[index]))
	{
		++index;
	}
	return atof(&buffer[begin]);
}

int Parser::ParseInteger()
{
	int begin = index;
	while (buffer[index] != '<' && buffer[index] != ',' && !isspace(buffer[index]))
	{
		++index;
	}
	return atoi(&buffer[begin]);
}

std::string Parser::ParseString()
{
	int begin = index;
	while (buffer[index] != '<' && buffer[index] != ',' && !isspace(buffer[index]))
	{
		++index;
	}
	return std::string(&buffer[begin],&buffer[index]);
}

void Parser::ParseTripleDouble(double * x, double * y, double * z)
{
	*x = ParseDouble();
	++index;
	*y = ParseDouble();
	++index;
	*z = ParseDouble();
}

void Parser::ParseCamera()
{
	Point position, focus;
	Vector up;
	double filedOfView;
	int xResolution, yResolution;
	while (HasNextTag())
	{
		std::string tag = NextTag();
		if (tag == "position")
		{
			SkipSpace();
			ParseTripleDouble(&position.x, &position.y, &position.z);
		}
		else if (tag == "up")
		{
			SkipSpace();
			ParseTripleDouble(&up.x, &up.y, &up.z);
		}
		else if (tag == "focus")
		{
			SkipSpace();
			ParseTripleDouble(&focus.x, &focus.y, &focus.z);
		}
		else if (tag == "fov")
		{
			SkipSpace();
			filedOfView = ParseDouble();
		}
		else if (tag == "resolution")
		{
			SkipSpace();
			xResolution = ParseInteger();
			++index;
			yResolution = ParseInteger();
		}
		else if (tag == "/camera")
		{
			double aspect = static_cast<double>(xResolution) / static_cast<double>(yResolution);
			camera = new Camera(position, focus, up, filedOfView, aspect);
			image = new Image(xResolution,yResolution);
			break;
		}
	}
}

void Parser::ParseRenderer()
{
	unsigned int bounce = 5;
	unsigned int samplesPerPixel = 4;
	while (HasNextTag())
	{
		std::string tag = NextTag();
		if (tag == "bounce")
		{
			SkipSpace();
			bounce = ParseInteger();
		}
		else if (tag == "sample")
		{
			SkipSpace();
			samplesPerPixel = ParseInteger();
		}
		else if (tag == "/renderer")
		{
			renderer = new Renderer(bounce, samplesPerPixel);
			break;
		}
	}
}

void Parser::ParseScene()
{
	scene = new Scene();
	while (HasNextTag())
	{
		std::string tag = NextTag();
		if (tag == "model")
		{
			Model *model = new Model;
			while (HasNextTag())
			{
				tag = NextTag();
				if (tag == "mesh")
				{
					MeshParser meshParser;
					meshParser.Parse(model, ParseString().c_str());
				}
				else if (tag == "sphere")
				{
					Point center;
					double radius;
					while (HasNextTag())
					{
						tag = NextTag();
						if (tag == "center")
						{
							ParseTripleDouble(&center.x, &center.y, &center.z);
						}
						else if (tag == "radius")
						{
							radius = ParseDouble();
						}
						else if (tag == "/sphere")
						{
							Sphere *sphere = new Sphere(center, radius);
							model->AddGeometry(sphere);
							break;
						}
					}
				}
				else if (tag == "material")
				{
					std::string type = ParseString();
					if (type == "diffuse")
					{
						model->bsdf = new DiffuseReflection(Color(1, 1, 1));
					}
					else if (type == "emit")
					{
						model->bsdf = new SpecularReflection(Color(1, 1, 1));
						model->emit.r = 12;
						model->emit.g = 12;
						model->emit.b = 12;
					}
				}
				else if (tag == "/model")
				{
					break;
				}
			}
			scene->AddModel(model);
		}
		else if (tag == "/scene")
		{
			break;
		}
	}
}
