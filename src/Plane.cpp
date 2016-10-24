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