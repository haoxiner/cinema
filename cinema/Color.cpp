#include "Color.h"

const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);

inline double CLAMP_COLOR(double value)
{
	/*if (value < 0.0)
	{
		return 0.0;
	}
	else if (value > 1.0)
	{
		return 1.0;
	}*/
	return value;
}

Color::Color() :r(0), g(0), b(0)
{
}

Color::Color(double rr, double gg, double bb):r(CLAMP_COLOR(rr)),g(CLAMP_COLOR(gg)),b(CLAMP_COLOR(bb))
{
}

Color::Color(double intensity)
{
	b = g = r = CLAMP_COLOR(intensity);
}

Color::~Color()
{
}

Color Color::operator+(const Color & c) const
{
	return Color(r + c.r, g + c.g, b + c.b);
}

Color& Color::operator+=(const Color & c)
{
	r = CLAMP_COLOR(r + c.r);
	g = CLAMP_COLOR(g + c.g);
	b = CLAMP_COLOR(b + c.b);
	return *this;
}

Color Color::operator*(const Color & c) const
{
	return Color(r * c.r, g * c.g, b * c.b);
}

Color & Color::operator*=(const Color & c)
{
	r = CLAMP_COLOR(r * c.r);
	g = CLAMP_COLOR(g * c.g);
	b = CLAMP_COLOR(b * c.b);
	return *this;
}

Color Color::operator*(const double f) const
{
	return Color(r*f, g*f, b*f);
}
