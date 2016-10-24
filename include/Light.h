#pragma once

#include "Vect3.h"
#include "Color.h"

class Light final {
public:
	Vect3 pos;
	Color color;
	
	Light() = delete;
	explicit Light(Vect3 p, Color c) : pos{p}, color{c} {}
	Light(Light const&) = default;
	Light& operator=(Light const&) = default;
};