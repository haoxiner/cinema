#pragma once
class Color
{
public:
	Color();
	Color(float rr, float gg, float bb);
	~Color();
	float r, g, b;
	static const Color BLACK;
	static const Color WHITE;
};

