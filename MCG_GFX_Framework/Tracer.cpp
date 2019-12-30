#include "Tracer.h"
#include "Sphere.h"
#include "Collision.h"
#include <vector>
#include "Ray.h"
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

void Tracer::addCamera(Camera* _camera)
{
	camera = _camera;
}

glm::vec3 Tracer::AntiAliasing(Ray _ray, glm::vec3 _Colour)
{
	glm::vec2 one = glm::vec2(_ray.pix.x - 0.5, _ray.pix.y - 0.5);
	glm::vec2 two = glm::vec2(_ray.pix.x + 0.5, _ray.pix.y - 0.5);
	glm::vec2 three = glm::vec2(_ray.pix.x + 0.5, _ray.pix.y + 0.5);
	glm::vec2 four = glm::vec2(_ray.pix.x - 0.5, _ray.pix.y + 0.5);

	glm::vec3 ColourOne = colourReturnAA(camera->rayCastOther(one));
	glm::vec3 ColourTwo = colourReturnAA(camera->rayCastOther(two));
	glm::vec3 ColourThree = colourReturnAA(camera->rayCastOther(three));
	glm::vec3 ColourFour = colourReturnAA(camera->rayCastOther(four));

	glm::vec3 colour = (ColourOne + ColourTwo + ColourThree + ColourFour + _Colour) / 5.0f;

	colour = colour;

	return colour;
}

glm::vec3 Tracer::colourReturn(Ray _ray)
{
	float inter = 0;
	Collision collide;
	glm::vec3 colour = background;
	for (int i = 0; i < objects.size(); i++) //run through each object
	{
		if (collide.sphereIntersect(_ray, objects.at(i)) == true) //if it hits the sphere
		{
			if (objects.at(i).t <= inter || !inter)
			{
				inter = objects.at(i).t;

				colour = objects.at(i).shadePixel(_ray,collide.intersectNormal(_ray,objects.at(i)),lights.at(0),camera);

				colour = AntiAliasing(_ray, colour);
			}
		}
	}

	return colour;
}

glm::vec3 Tracer::colourReturnAA(Ray _ray)
{
	float inter = 0;
	Collision collide;
	glm::vec3 colour = background;
	for (int i = 0; i < objects.size(); i++) //run through each object
	{
		if (collide.sphereIntersect(_ray, objects.at(i)) == true) //if it hits the sphere
		{
			if (objects.at(i).t <= inter || !inter)
			{
				inter = objects.at(i).t;

				colour = objects.at(i).shadePixel(_ray, collide.intersectNormal(_ray, objects.at(i)), lights.at(0), camera);
			}
		}
	}
	return colour;
}

Tracer::~Tracer()
{
}

Tracer::Tracer()
{

}
