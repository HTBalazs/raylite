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

#include <thread>
#include <algorithm>
#include "RayTracer.h"

#define random(min, max) (((float)(rand()%1000)/1000.0f)*((max)-(min))+(min))

void RayTracer::render(std::string filename, int w, int h, ScenePtr& scene, unsigned int aasamples, unsigned int dfsamples, unsigned int maxBounces) const {
	std::mutex mtx;
	// Smart pointers for pixel color and pixel depth
	PixelDataPtr<Color> color{new PixelData<Color>{w*h}};
	PixelDataPtr<float> depth{new PixelData<float>{w*h}};

	float ratio = (float)w/h;
	float dx = 1.0/w*ratio;
	float dy = 1.0/h;

	// process for a single thread
	auto process = [&] (int h_begin, int h_end, int v_begin, int v_end) {	
		float ratio = (float)w/h;
		float dx = 1.0/w*ratio;
		float dy = 1.0/h;
	
		// Iterate through pixels
		float dpx = sin((float)scene->camera->perspective);
		float dpy = sin((float)scene->camera->perspective)/ratio;
	
		float y = -dpy+v_begin*dpy/h*2;
		for(int j=v_begin; j<=v_end; j++) {   // loop over pixels (vertical)
			y += 2*dpy/h;
			float x = -dpx+h_begin*dpx/w*2;
			for(int i=h_begin; i<=h_end; i++) {   // loop over pixels (horizontal)
				x += 2*dpx/w;
				for(int df=0; df<dfsamples; df++) {   // depth blur - random sampling
					float range = dfsamples==1?0.0f:(float)dfsamples/2.0f;
					//samples in yawing and pitching directions
					float dfx = random(-range, range) / dfsamples;
					float dfy = random(-range, range) / dfsamples;
					// temporal camera object 
					std::unique_ptr<Camera> tmpcam{scene->camera->rotateCamera(dfx, dfy)};
	
					// Calculate direction of the current pixel
					Vect3 pixeldir = (tmpcam->direction + tmpcam->right*x + tmpcam->up*y).normalize();
					
					for(int aasx=0; aasx<aasamples; aasx++) {   // antialiasing - sampling in x and y direction
						for(int aasy=0; aasy<aasamples; aasy++) {
							Vect3 sampledir = (pixeldir + tmpcam->right*dx*((float)aasx/aasamples-0.5f) + tmpcam->up*dy*((float)aasy/aasamples-0.5f)).normalize();
							unsigned int bounces = 0;
							// Launch ray in sampledir
							Rayptr ray{new Ray{tmpcam->pos, sampledir}};
							unsigned int aasamples2 = aasamples*aasamples; // number of aa samples
							color->data[j*w+i] += scene->getRayColor(ray, depth->data[j*w+i], bounces, maxBounces)/(float)aasamples2/(float)dfsamples;
							mtx.lock();
							rays.push_back(*ray);
							mtx.unlock();
						}
					}
				}
			}
		}
	};

	std::vector<std::thread> th;

	int sqsize = 200;

	// divide image to squares and process each square independently on different threads
	int h_begin = 0;
	int h_end = -1;
	while(h_end<w-1) {
		h_end += sqsize;
		if(h_end>w) {
			h_end = w-1;
		}
		int v_begin = 0;
		int v_end = -1;
		while(v_end<h-1) {
			v_end += sqsize;
			if(v_end>h) {
				v_end = h-1;
			}
			th.push_back(std::thread{process, h_begin, h_end, v_begin, v_end});
			v_begin = v_end+1;
		}
		h_begin = h_end+1;
	}
	for(auto& it : th) {
		it.join();
	}

	// Save pixel colors to BMP
	savebmp(filename, w, h, color);
}

std::vector<Ray> const& RayTracer::getRays() const {
	return rays;
}
