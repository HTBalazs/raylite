#pragma once

#include "Object.h"

class Plane final : public Object
{
public:
	Vect3 normal;
	Color color1;
	Color color2;
	float gridsize;
	
	Plane() = delete;
	explicit Plane(Vect3, Vect3, float, Material);
	Plane(Plane const&) = default;
	Plane& operator=(Plane const&) = default;

	Vect3 getIntersection(Rayptr const&, bool&) const override;
	Vect3 getNormal(Rayptr const&, Vect3&) const override;
	Color getColor(Rayptr const&) const override;
};


