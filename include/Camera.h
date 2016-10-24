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