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

#include "Scene.h"

Object* Scene::findClosestObject(Rayptr const& ray, float& depth) const {
	float closest = 1e6;
	Object* intersected = nullptr;

	for(auto it : object) {
		float itdist = it->getDistance(ray);
		if(closest>itdist) {
			closest = itdist;
			intersected = it;
		}
	}

	depth = closest;

	return intersected;
}

Scene::~Scene() {
	light.clear();
	object.clear();
}

void Scene::addCamera(std::shared_ptr<Camera> camptr) {
	camera = std::move(camptr);
}

void Scene::addLight(Light* obj) {
	light.push_back(obj);
}

Color Scene::getLighting(Object const* is, Rayptr const& newray, Rayptr const& shadowray, Vect3 const& normal,  Light* light) const {
	float depth;
	Object* obstacle = findClosestObject(shadowray, depth);
	
	float distance = (light->pos-shadowray->start).magnitude();

	if(obstacle != nullptr || distance>depth) {
		return Color(0,0,0,1);
	} else {
		float di = shadowray->direction*normal; // diffuse 
		float sp = shadowray->direction*newray->direction; // specular
		return is->material.k_d*(di<0?0:di)*light->color + is->material.k_s*(sp<0?0:pow(sp+0.025,is->material.shininess))*light->color;
	}
}

Vect3 Scene::reflectVector(Vect3 dir, Vect3 const& normal) const {
	return (dir - 2*(dir*normal)*normal).normalize();
}

Ray* Scene::reflectRay(Rayptr const& oldray, Vect3 const& intersectionpoint, Vect3 const& normal) const {
	return new Ray{intersectionpoint, reflectVector(oldray->direction, normal)};
}

Color Scene::getRayColor(Rayptr oldray, float& depth, unsigned int numBounces, unsigned int const maxBounce) const {
	// Get closest object (==nullptr if no intersection)
	Object* intersected = findClosestObject(oldray, depth);

	oldray->length = depth;

	if(intersected == nullptr) {
		return bg;
	} else if(intersected->terminal) {
		return intersected->material.color1;
	}

	Vect3 ip;
	Vect3 normal = intersected->getNormal(oldray, ip);
	Rayptr newray{reflectRay(oldray, ip, normal)};

	// Color of the intersection point with ambient light
	Color illumination = i_a*intersected->material.k_a*intersected->getColor(newray);
	
	// Lights (launch shadowrays to all light positions in the scene)
	for(auto it : light) {
		Vect3 tolight = (it->pos-newray->start).normalize();
		Rayptr shadowray{new Ray{newray->start + tolight*0.001, tolight}};
		illumination += getLighting(intersected, newray, shadowray, normal, it);
	}

	// Reflection
	float currentdepth;
	if(numBounces<maxBounce) {
		illumination +=  intersected->material.fresnel*getRayColor(newray, currentdepth, ++numBounces, maxBounce);
		oldray->length += newray->length;
	}

	return illumination;
}