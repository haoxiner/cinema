#pragma once

class Color;
class Image
{
public:
	Image(unsigned int width, unsigned int height);
	~Image();
	void SetColor(const unsigned int x, const unsigned int y, const Color &color);
private:
	unsigned int *data;
	const unsigned int xResolution;
	const unsigned int yResolution;
};


