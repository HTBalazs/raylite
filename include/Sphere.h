#pragma once

#include "Object.h"

class Sphere final : public Object {
private:
	Vect3 getProjectionPoint(Rayptr const& ray) const;
public:
	float radius;
	
	Sphere() = delete;
	explicit Sphere(Vect3, float, Material);
	Sphere(Sphere const&) = default;
	Sphere& operator=(Sphere const&) = default;

	Vect3 getIntersection(Rayptr const&, bool&) const override;
	Vect3 getNormal(Rayptr const&, Vect3&) const override;
	Color getColor(Rayptr const&) const override;
};