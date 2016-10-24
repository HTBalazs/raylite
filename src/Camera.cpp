#include "Camera.h"
#include <cmath>

Camera::Camera(Vect3 p, Vect3 c, float ap, float pr) {
	pos = p;
	center = c;
	
	direction = center-pos;
	direction = direction.normalize();
	right = crossProduct(direction, Vect3{0,1,0}).normalize();
	up = crossProduct(right, direction).normalize();

	aperture = ap;
	perspective = pr/180.0f*3.1415f;
}

// generate new camera
Camera* Camera::rotateCamera(float pitch, float yaw)
{
	pitch *= aperture;
	yaw *= aperture;
	Vect3 y(0,1,0);
	float a = center.x;
	float b = center.y;
	float c = center.z;
	float u = right.x;
	float v = right.y;
	float w = right.z;

	float t1 = (a*(v*v+w*w)-u*(b*v+c*w-u*pos.x-v*pos.y-w*pos.z))*(1-cos(yaw))+pos.x*cos(yaw)+(-c*v+b*w-w*pos.y+v*pos.z)*sin(yaw);
	float t2 = (b*(u*u+w*w)-v*(a*u+c*w-u*pos.x-v*pos.y-w*pos.z))*(1-cos(yaw))+pos.y*cos(yaw)+(c*u-a*w+w*pos.x-u*pos.z)*sin(yaw);
	float t3 = (c*(u*u+v*v)-w*(a*u+b*v-u*pos.x-v*pos.y-w*pos.z))*(1-cos(yaw))+pos.z*cos(yaw)+(-b*u+a*v-v*pos.x+u*pos.y)*sin(yaw);

	Vect3 tmppos{t1,t2,t3};
	Vect3 tmpup = crossProduct(right, direction).normalize();

	u = tmpup.x;
	v = tmpup.y;
	w = tmpup.z;

	t1 = (a*(v*v+w*w)-u*(b*v+c*w-u*tmppos.x-v*tmppos.y-w*tmppos.z))*(1-cos(pitch))+tmppos.x*cos(pitch)+(-c*v+b*w-w*tmppos.y+v*tmppos.z)*sin(pitch);
	t2 = (b*(u*u+w*w)-v*(a*u+c*w-u*tmppos.x-v*tmppos.y-w*tmppos.z))*(1-cos(pitch))+tmppos.y*cos(pitch)+(c*u-a*w+w*tmppos.x-u*tmppos.z)*sin(pitch);
	t3 = (c*(u*u+v*v)-w*(a*u+b*v-u*tmppos.x-v*tmppos.y-w*tmppos.z))*(1-cos(pitch))+tmppos.z*cos(pitch)+(-b*u+a*v-v*tmppos.x+u*tmppos.y)*sin(pitch);

	tmppos = Vect3{t1,t2,t3};

	return new Camera{tmppos, center, aperture, perspective};
}