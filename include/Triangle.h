#pragma once

#include "Object.h"
#define sgn(a) (((a)<0)?(-1):(((a)==0)?(0):(1)))

class Triangle final : public Object {
public:
	Vect3 p1, p2, p3;
	Vect3 normal;
	
	Triangle() = delete;
	explicit Triangle(Vect3, Vect3, Vect3, Material);	
	Triangle(Triangle const&) = default;
	Triangle& operator=(Triangle const&) = default;

	Vect3 getIntersection(Rayptr const&, bool&) const override;	
	Vect3 getNormal(Rayptr const&, Vect3&) const override;
	Color getColor(Rayptr const&) const override;
};