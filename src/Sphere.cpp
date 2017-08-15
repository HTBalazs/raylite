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

#include "Sphere.h"

Vect3 Sphere::getProjectionPoint(Rayptr const& ray) const {
	return ray->direction*((pos-ray->start)*ray->direction) + ray->start;
}

Sphere::Sphere(Vect3 position, float rad, Material mat) {
	pos = position;
	radius = rad;
	material = mat;
}

Vect3 Sphere::getIntersection(Rayptr const& ray, bool& intersect) const {
	const Vect3& A = ray->start;
	const Vect3  B = getProjectionPoint(ray);
	const Vect3& C = pos;
	
	float a = (B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y) + (B.z-A.z)*(B.z-A.z);
	float b = 2*((B.x-A.x)*(A.x-C.x) + (B.y-A.y)*(A.y-C.y) + (B.z-A.z)*(A.z-C.z));
	float c = (A.x-C.x)*(A.x-C.x) + (A.y-C.y)*(A.y-C.y) + (A.z-C.z)*(A.z-C.z) - radius*radius;
	
	float delta = b*b-4*a*c;
	
	if(delta > 0) {
		intersect = true;
		float d1 = (-b-sqrt(delta))/2/a;
		float d2 = (-b+sqrt(delta))/2/a;
		
		Vect3 intsec1 = Vect3(A.x+d1*(B.x-A.x), A.y+d1*(B.y-A.y), A.z+d1*(B.z-A.z));
		Vect3 intsec2 = Vect3(A.x+d2*(B.x-A.x), A.y+d2*(B.y-A.y), A.z+d2*(B.z-A.z));
		
		if(ray->direction*(intsec1-ray->start) < 0.0001) {
			intersect = false;
			return Vect3(0,0,0);
		}
		
		if(Vect3{intsec1-A}.magnitude()<Vect3{intsec2-A}.magnitude()) {
			return intsec1;
		} else {
			return intsec2;
		}
	} else {
		intersect = false;
		return Vect3(0,0,0);
	}
}

Vect3 Sphere::getNormal(Rayptr const& ray, Vect3& ip) const {
	bool intersect = false;
	ip = getIntersection(ray, intersect);
	return (ip-pos).normalize();
}

Color Sphere::getColor(Rayptr const&) const {
	return material.color1;
}