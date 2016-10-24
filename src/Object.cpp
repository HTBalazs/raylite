#include "Object.h"

float Object::getDistance(Rayptr const& ray) const {
	bool intersect = false;
	Vect3 intsec = getIntersection(ray, intersect);
	
	if(!intersect) {
		return 1e7;
	} else {
		return (intsec-ray->start).magnitude();
	}
}