#pragma once
#include <string>
class Camera;
class Scene;
class Image;
class Renderer;
class Parser
{
public:
	Parser();
	~Parser();
	void Parse(const char *filepath);
	Camera * GetCamera();
	Scene * GetScene();
	Image * GetImage();
	Renderer * GetRenderer();
private:
	bool HasNextTag();
	std::string NextTag();
	void SkipSpace();
	double ParseDouble();
	int ParseInteger();
	std::string ParseString();
	void ParseTripleDouble(double *x, double *y, double *z);
	void ParseCamera();
	void ParseRenderer();
	void ParseScene();
private:
	std::string buffer;
	unsigned int index;
private:
	Camera *camera;
	Scene *scene;
	Image *image;
	Renderer *renderer;
};

