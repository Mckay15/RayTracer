#include "Tracer.h"
//#include "Sphere.h"
#include "Collision.h"
#include <vector>
#include "Camera.h"
//#include "Light.h"

void Tracer::addSphere(glm::vec3 _centre, float _radius)
{
	Sphere sphere(_centre, _radius);
	objects.push_back(sphere);
}

void Tracer::addLight(glm::vec3 _pos, glm::vec3 _colour)
{
	Light light(_pos, _colour);
	lights.push_back(light);
}

void Tracer::addCamera(Camera _camera)
{
	camera = _camera;
}

glm::vec3 Tracer::colourReturn(Ray _ray)
{
	float inter = 0;
	Collision collide;
	glm::vec3 colour = background;
	for (int i = 0; i < objects.size(); i++)
	{
		if (collide.sphereIntersect(_ray, objects.at(i)) == true)
		{
			if (objects.at(i).t <= inter || !inter)
			{
				inter = objects.at(i).t;

				colour = objects.at(i).shadePixel(_ray,collide.intersectNormal(_ray,objects.at(i)),lights.at(0),camera);
			}
		}
	}
	return colour;
}
