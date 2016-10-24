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