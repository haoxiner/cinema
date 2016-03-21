#include "Color.h"

const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);

inline float CLAMP_COLOR(float value)
{
	if (value < 0.0f)
	{
		return 0.0f;
	}
	else if (value > 1.0f)
	{
		return 1.0f;
	}
	return value;
}

Color::Color() :r(0), g(0), b(0)
{
}

Color::Color(float rr, float gg, float bb):r(CLAMP_COLOR(rr)),g(CLAMP_COLOR(gg)),b(CLAMP_COLOR(bb))
{
}

Color::Color(float intensity)
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
	r *= c.r;
	g *= c.g;
	b *= c.b;
	return *this;
}

Color Color::operator*(const float f) const
{
	return Color(r*f, g*f, b*f);
}
