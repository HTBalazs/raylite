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
#include <cmath>

class Vect3 final {
public:
	float x;
	float y;
	float z;

	explicit Vect3() : x{0}, y{0}, z{0} {}
	Vect3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	float magnitude() const	{ return sqrt(x*x+y*y+z*z); }
	Vect3 normalize() const	{ return Vect3{x/magnitude(), y/magnitude(), z/magnitude()}; }
};

inline Vect3 operator+(Vect3 v1, Vect3 v2)
{
	return Vect3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

inline Vect3& operator+=(Vect3& v1, Vect3 v2)
{
	v1 = v1 + v2;
	return v1;
}

inline Vect3 operator-(Vect3 v1, Vect3 v2)
{
	return Vect3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

inline Vect3 operator-(Vect3 v)
{
	return Vect3(-v.x, -v.y, -v.z);
}

inline float operator*(Vect3 v1, Vect3 v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline Vect3 operator*(Vect3 v, float s)
{
	return Vect3(v.x*s, v.y*s, v.z*s);
}

inline Vect3 operator*(float s, Vect3 v)
{
	return Vect3(v.x*s, v.y*s, v.z*s);
}

inline Vect3 operator/(Vect3 v, float s)
{
	return Vect3(v.x/s, v.y/s, v.z/s);
}

inline Vect3 crossProduct(Vect3 v1, Vect3 v2)
{
	return Vect3(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}

inline std::ostream& operator<<(std::ostream& os, Vect3 v)
{
	os << v.y << ' ' << v.y << ' ' << v.z;
	return os;
}

