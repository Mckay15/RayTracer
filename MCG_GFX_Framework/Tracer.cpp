#include "Tracer.h"
#include "Collision.h"
#include <vector>
#include "Ray.h"
#include <random>
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

glm::vec3 Tracer::AntiAliasing(Ray _ray, glm::vec3 _Colour)
{
	glm::vec3 colour = glm::vec3(0,0,0);
	float amount = 0;

	glm::vec2 one = glm::vec2(_ray.pix.x - 0.5, _ray.pix.y - 0.5);
	glm::vec2 two = glm::vec2(_ray.pix.x + 0.5, _ray.pix.y - 0.5);
	glm::vec2 three = glm::vec2(_ray.pix.x + 0.5, _ray.pix.y + 0.5);
	glm::vec2 four = glm::vec2(_ray.pix.x - 0.5, _ray.pix.y + 0.5);

	AA[0] = colourReturnAA(camera.rayCast(one));
	AA[1] = colourReturnAA(camera.rayCast(two));
    AA[2] = colourReturnAA(camera.rayCast(three));
	AA[3] = colourReturnAA(camera.rayCast(four));

	for (int i = 0; i < 4; i++)
	{
		//bool temp = glm::all(glm::lessThan(AA[i] - _Colour, glm::vec3(25, 25, 25)));
		//temp = glm::all(glm::lessThan(glm::vec3(-25, -25, -25), AA[i] - _Colour));
		if (glm::all(glm::lessThan(AA[i] - _Colour, glm::vec3(tol, tol, tol))) == false ||
			glm::all(glm::lessThan(glm::vec3(-tol, -tol, -tol), AA[i] - _Colour)) == false)
		{
			colour = colour + AA[i] + AARandom(_ray);
			amount += 5;
		}
		else
		{
			colour = colour + AA[i];
			amount++;
		}
	}

	colour = (colour + _Colour) / (amount + 1);

	return colour;
}

glm::vec3 Tracer::AARandom(Ray _ray)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

	float temp = dist(rng);

	glm::vec2 one = glm::vec2(_ray.pix.x - (0.5 - (dist(rng)/400.0f)), _ray.pix.y - (0.5 - (dist(rng) / 400.0f)));
	glm::vec2 two = glm::vec2(_ray.pix.x + (0.5 - (dist(rng) / 400.0f)), _ray.pix.y - (0.5 - (dist(rng) / 400.0f)));
	glm::vec2 three = glm::vec2(_ray.pix.x + (0.5 - (dist(rng) / 400.0f)), _ray.pix.y + (0.5 - (dist(rng) / 400.0f)));
	glm::vec2 four = glm::vec2(_ray.pix.x - (0.5 - (dist(rng) / 400.0f)), _ray.pix.y + (0.5 - (dist(rng) / 400.0f)));

	glm::vec3 ColourOne = colourReturnAA(camera.rayCast(one));
	glm::vec3 ColourTwo = colourReturnAA(camera.rayCast(two));
	glm::vec3 ColourThree = colourReturnAA(camera.rayCast(three));
	glm::vec3 ColourFour = colourReturnAA(camera.rayCast(four));

	glm::vec3 colour = (ColourOne + ColourTwo + ColourThree + ColourFour);

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
