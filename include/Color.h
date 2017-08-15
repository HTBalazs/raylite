/*
    Copyright 2016-2017 Balazs Toth
    This file is part of Raylite.

    Raylite is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Raylite is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Raylite.  If not, see <http://www.gnu.org/licenses/>.

    For more information please visit: https://bitbucket.org/Rayliteproject/
*/

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