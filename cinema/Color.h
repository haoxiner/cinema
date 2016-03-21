#pragma once
class Color
{
public:
	Color();
	Color(float rr, float gg, float bb);
	Color(float intensity);
	~Color();
	Color operator+(const Color &c)const;
	Color & operator+=(const Color &c);
	Color operator*(const Color &c)const;
	Color & operator*=(const Color &c);
	Color operator*(const float f)const;
public:
	float r, g, b;
	static const Color BLACK;
	static const Color WHITE;
};

