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

#include <vector>
#include <memory>
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Light.h"
#include "Camera.h"

class Scene final {
private:
	Object* findClosestObject(Rayptr const& ray, float&) const;
	Color getLighting(Object const*, Rayptr const&, Rayptr const&, Vect3 const&, Light*) const;
	Ray* reflectRay(Rayptr const&, Vect3 const&, Vect3 const&) const;
	Vect3 reflectVector(Vect3, Vect3 const&) const;
	
public:
	std::shared_ptr<Camera> camera;
	std::vector<Object*> object;
	std::vector<Light*> light;
	Color bg;
	Color i_a;
	
	Scene() = delete;
	explicit Scene(Color background, Color ambient) : bg{background}, i_a{ambient} {}
	Scene(Scene const& other) = default;
	Scene(Scene&& other) = default;
	Scene& operator=(Scene const&) = default;
	Scene& operator=(Scene&&) = default;

	~Scene();
	template <typename T> void addObject(T*);
	void addCamera(std::shared_ptr<Camera>);
	void addLight(Light*);
	Color getRayColor(Rayptr, float&, unsigned int, unsigned int const) const;
};

// add different types of objects
template <typename T>
inline void Scene::addObject(T* obj) {
	object.push_back(obj);
}

using ScenePtr = std::shared_ptr<Scene>;