#pragma once
#include <string>

class Color;
class Image
{
public:
	Image(unsigned int width, unsigned int height);
	~Image();
	void SetColor(const unsigned int x, const unsigned int y, const Color &color);
	void WriteToFile(const std::string filename);
private:
	uint8_t *m_data;
	const unsigned int m_xResolution;
	const unsigned int m_yResolution;
};


