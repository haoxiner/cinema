#include "Image.h"
#include "Color.h"

Image::Image(unsigned int width, unsigned int height):
	xResolution(width),yResolution(height),
	data(new unsigned int[xResolution * yResolution * 3])
{
}

Image::~Image()
{
}

void Image::SetColor(unsigned int x, unsigned int y, const Color &color)
{
	unsigned int *location = data + y * yResolution + x;
	*data = static_cast<unsigned int>(color.r * 255);
	++data;
	*data = static_cast<unsigned int>(color.g * 255);
	++data;
	*data = static_cast<unsigned int>(color.b * 255);
}