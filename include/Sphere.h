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