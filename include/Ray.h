#pragma once 

#include <memory>

class Ray final {
public:
	Vect3 start;
	Vect3 direction;
	
	Ray() = delete;
	explicit Ray(Vect3 s, Vect3 d) : start{s}, direction{d.normalize()} {}
	Ray(Ray const&) = default;
	Ray& operator=(Ray const&) = default;
};

using Rayptr = std::shared_ptr<Ray>;