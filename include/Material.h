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

struct Material{
	float k_a;
	float k_d;
	float k_s;
	float shininess;
	float fresnel;
	Color color1;
	Color color2;
	
	explicit Material() : k_a{0.1}, k_d{0.1}, k_s{0.1}, shininess{10}, fresnel{0.1}, color1{1,1,0,1}, color2{0,1,1,1} {}
	explicit Material(float ka, float kd, float ks, float sh, float fr, Color c1, Color c2) : k_a{ka}, k_d{kd}, k_s{ks}, shininess{sh}, fresnel{fr}, color1{c1}, color2{c2} {}
};