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

#include "Plane.h"

Plane::Plane(Vect3 p, Vect3 n, float gs, Material mat) {
	pos = p;
	normal = n.normalize();
	gridsize = gs;
	material = mat;
}
	
Vect3 Plane::getIntersection(Rayptr const& ray, bool& intersect) const {
	float vn = ray->direction*normal;
	
	// return if the ray is parallel with the plane
	if(vn==0) {
		intersect = false;
		return Vect3(-1,-1,-1);
	}
	
	float d = (pos-ray->start)*normal / vn;
	
	Vect3 tmp = Vect3{d*ray->direction.x, d*ray->direction.y, d*ray->direction.z};
	Vect3 p = tmp + ray->start;
	
	// return if intersection occurs at the wrong side of the ray (backwards)
	if(tmp*ray->direction < 0.0001) {
		intersect = false;
		return Vect3(-1,-1,-1);
	}

	intersect = true;
	return p;
}

Vect3 Plane::getNormal(Rayptr const& ray, Vect3& ip) const {
	bool intersect = false;
	ip = getIntersection(ray, intersect);
	return normal;
}

Color Plane::getColor(Rayptr const& ray) const {
	Color c = (((((int)floor((ray->start.x-pos.x)/gridsize)) + (int)floor((ray->start.z-pos.z)/gridsize))%2) == 0) ? material.color1 : material.color2;
	
	return c;
}