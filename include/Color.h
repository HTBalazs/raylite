#pragma once

#include <iostream>
#include <stdio.h>

class Color {
public:
	float r;
	float g;
	float b;
	float a;
	explicit Color() : r{0}, g{0}, b{0}, a{0} {}
	Color(float rr, float gg, float bb, float aa) : r{rr>1?1:rr}, g{gg>1?1:gg}, b{bb>1?1:bb}, a{aa>1?1:aa} {}
	Color(Color const&) = default;
};

inline Color operator+(Color c1, Color c2)
{
	return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b, c1.a+c2.a);
}

inline Color& operator+=(Color& c1, Color c2)
{
	c1 = c1 + c2;
	return c1;
}

inline Color operator/(Color c, float s)
{
	return Color(c.r/s, c.g/s, c.b/s, c.a);
}

inline Color operator*(Color c, float s)
{
	return Color(c.r*s, c.g*s, c.b*s, c.a*s);
}

inline Color operator*(float s, Color c)
{
	return Color(c.r*s, c.g*s, c.b*s, c.a*s);
}

inline Color operator*(Color c1, Color c2)
{
	return Color(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b, c1.a*c2.a);
}

inline std::ostream& operator&(std::ostream& os, Color c)
{
	os << c.r << ' ' << c.g << ' ' << c.b << ' ' << c.a;
	return os;
}