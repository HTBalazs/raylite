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

#include "Triangle.h"

Triangle::Triangle(Vect3 point1, Vect3 point2, Vect3 point3, Material mat, bool tr/*=false*/) {
	p1=point1;
	p2=point2;
	p3=point3;
	pos = (p1+p2+p3)/3;
	normal = crossProduct(point2-point1, point3-point1).normalize();
	material = mat;
	terminal = tr;
};

Vect3 Triangle::getIntersection(Rayptr const& ray, bool& intersect) const {
	float vn = ray->direction*normal;

	if(vn==0) {
		intersect = false;
		return Vect3(0,0,0);
	}

	float d = (pos-ray->start)*normal / vn;
	Vect3 tmp = d*ray->direction;
	Vect3 prj = tmp + ray->start;

	Vect3 tmpvec1 = p3 - p1;
	Vect3 tmpvec2 = p2 - p1;
	Vect3 tmpvec3 = prj - p1;

	Vect3 bar1 = crossProduct(tmpvec1, tmpvec2);
	Vect3 bar2 = crossProduct(tmpvec1, tmpvec3);
	Vect3 bar3 = crossProduct(tmpvec3, tmpvec2);

	Vect3 u = Vect3{bar1.magnitude(), bar2.magnitude(), bar3.magnitude()};

	float vi = u.y / u.x * sgn(bar1*bar2);
	float wi = u.z / u.x * sgn(bar1*bar3);
	
	if(vi >= 0.0f && wi >= 0.0f && vi + wi <= 1.0f && (prj-ray->start)*ray->direction>0.001) {
		intersect = true;
		return prj;
	} else {
		intersect = false;
		return Vect3(0,0,0);
	}
}

Vect3 Triangle::getNormal(Rayptr const& ray, Vect3& ip) const {
	bool intersect = false;
	ip = getIntersection(ray, intersect);
	return normal;
}

Color Triangle::getColor(Rayptr const& ray) const {
	return material.color1;
}