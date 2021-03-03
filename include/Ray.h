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

#include <memory>

class Ray final {
public:
	Vect3 start;
	Vect3 direction;
    float length;
	
	Ray() = delete;
	explicit Ray(Vect3 s, Vect3 d) : start{s}, direction{d.normalize()} {}
	Ray(Ray const&) = default;
	Ray& operator=(Ray const&) = default;
};

using Rayptr = std::shared_ptr<Ray>;