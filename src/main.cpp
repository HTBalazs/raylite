#include "RayTracer.h"
/*
Info:
	Material{ambient, diffuse, specular, shininess, Fresnel, color1, color2}
	Scene{background, ambient intensity}
	Sphere{center position, material}
	Plane{position, normal, material}
	Light{position, color}
	Camera{camera position, center position, aperture size, perspective angle(deg)}
	RayTracer{}
	RayTracer::render(file name, width in pixels, height in pixels, scene object, vertical and horizontal antialiasing samples, vertical and horizontal depth field samples, maximum ray bounces)
	Scene::addObject(Sphere or Plane object)
	Scene::addLight(Light object)
	Scene::addCamera(Camera object)
*/

int main()
{
	// materials
	std::vector<Material> mat;
	mat.push_back(Material{0.5,0.5,0.2,100,1.0,Color{1.0,0.4,1.0,1.0}, Color{1.0,0.4,1.0,1.0}});
	mat.push_back(Material{0.6,0.1,1,300,1,Color{0.2,0.2,0.2,1.0}, Color{0.2,0.2,0.2,1.0}});
	mat.push_back(Material{0.5,0.5,0.2,100,0.2,Color{0.6,0.8,0.0,1.0}, Color{0.6,0.8,0.0,1.0}});
	mat.push_back(Material{0.6,0.6,0.2,100,0.7,Color{1.0,0.7,0.0,1.0}, Color{1.0,0.4,1.0,1.0}});
	mat.push_back(Material{0.5,0.7,0.05,50,0.1,Color{0.0,0.7,0.9,1.0}, Color{0.0,0.7,0.9,1.0}});
	mat.push_back(Material{0.5,0.1,0.3,1  ,0.2,Color{0.0,0.0,0.0,1.0}, Color{1.0,1.0,1.0,1.0}});

	// smart pointer for the scene object
	ScenePtr scene{new Scene{Color{0,0,0,1}, Color{0.5,0.5,0.5,1}}};
	scene->addObject(new Sphere{Vect3{-0.5,0.5,0.5}, 0.5, mat[0]});
	scene->addObject(new Sphere{Vect3{0.25,0.25,0.5}, 0.25, mat[1]});
	scene->addObject(new Sphere{Vect3{0.75,0.2,0.75}, 0.2, mat[2]});
	scene->addObject(new Sphere{Vect3{0.0,0.15,1.0}, 0.15, mat[3]});
	scene->addObject(new Sphere{Vect3{0.75,0.3,0}, 0.3, mat[4]});

	scene->addObject(new Plane{Vect3{0,0,0}, Vect3{0,1,0}, 0.25, mat[5]});
	scene->addLight(new Light{Vect3{0.5,1.2,0}, Color{1,1,1,1}});
	scene->addCamera(std::shared_ptr<Camera>{new Camera{Vect3{1.05,0.8,1.95}, Vect3{0.3,0.3,0.5}, 0.02, 60}});

	// smart pointer for the raytracer object
	RayTracerPtr raytracer{new RayTracer{}};
	/*
	raytracer->render("preview.bmp", 960, 540, scene, 1, 1, 1); 		// fast but coarse
	//*/ raytracer->render("final.bmp", 1920, 1080, scene, 2, 25, 3); 	// slow but nice

	return 0;
}