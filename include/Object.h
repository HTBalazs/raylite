#pragma once

#include <memory>
#include "Vect3.h"
#include "Ray.h"
#include "Color.h"
#include "Material.h"

class Object {
public:
	Vect3 pos;
	Material material;

	// Object(Object const&) = default;
	// Object& operator=(Object const&) = default;
	
	float getDistance(Rayptr const& ray) const;
	virtual Vect3 getIntersection(Rayptr const&, bool&) const = 0;
	virtual Vect3 getNormal(Rayptr const&, Vect3&) const = 0;
	virtual Color getColor(Rayptr const&) const = 0;
};