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

#include "Vect3.h"

class Camera final {
public:
	Vect3 pos;
	Vect3 center;
	Vect3 up;
	Vect3 right;
	Vect3 direction;
	float aperture;
	float perspective;
	
	Camera() = delete;
	explicit Camera(Vect3, Vect3, float, float);
	Camera(Camera const&) = default;
	Camera& operator=(Camera&) = default;
	
	Camera* rotateCamera(float, float);
};