#pragma once
class Color
{
public:
	Color();
	Color(double rr, double gg, double bb);
	Color(double intensity);
	~Color();
	Color operator+(const Color &c)const;
	Color & operator+=(const Color &c);
	Color operator*(const Color &c)const;
	Color & operator*=(const Color &c);
	Color operator*(const double f)const;
	bool operator==(const Color &c)const;
	bool operator!=(const Color &c)const;
public:
	double r, g, b;
	static const Color BLACK;
	static const Color WHITE;
};

