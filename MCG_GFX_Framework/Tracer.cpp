#include "Tracer.h"
#include "Collision.h"
#include <vector>
#include "Ray.h"
#include <random>
#include <iostream>
//#include "Light.h"

void Tracer::addSphere(glm::vec3 _centre, float _radius)
{
	Sphere sphere(_centre, _radius);  //adds a sphere
	objects.push_back(sphere);
}

void Tracer::addLight(glm::vec3 _pos, glm::vec3 _colour)
{
	Light light(_pos, _colour); // adds a light
	lights.push_back(light);
}

void Tracer::addCamera(Camera _camera)
{
	camera = _camera; //adds the camera
}

glm::vec3 Tracer::AntiAliasing(Ray _ray, glm::vec3 _Colour)
{
	glm::vec3 colour = glm::vec3(0,0,0);
	float amount = 0;
	raysFired = 0; 
	//sends out rays for sampling revlative to pixel
	glm::vec2 one = glm::vec2(_ray.pix.x - 1, _ray.pix.y - 1);
	glm::vec2 two = glm::vec2(_ray.pix.x + 1, _ray.pix.y - 1);
	glm::vec2 three = glm::vec2(_ray.pix.x + 1, _ray.pix.y + 1);
	glm::vec2 four = glm::vec2(_ray.pix.x - 1, _ray.pix.y + 1); 

	AA[0] = colourReturnAA(camera.rayCast(one));
	AA[1] = colourReturnAA(camera.rayCast(two));
    AA[2] = colourReturnAA(camera.rayCast(three));
	AA[3] = colourReturnAA(camera.rayCast(four));

	for (int i = 0; i < 4; i++)
	{
		glm::vec3 tmpp = AA[i] - _Colour;

		//bool temp = glm::all(glm::lessThan(AA[i] - _Colour, glm::vec3(tol, tol, tol)));
		//bool temp2 = glm::all(glm::lessThan(glm::vec3(-tol, -tol, -tol), AA[i] - _Colour));


		//Checks if any of the rays casted are beyond the tolerance
		if (glm::all(glm::lessThan(AA[i] - _Colour, glm::vec3(tol, tol, tol))) == false
			|| glm::all(glm::lessThan(glm::vec3(-tol, -tol, -tol), AA[i] - _Colour)) == false)
		{
			colour = colour + AA[i] + AARandom(_ray,i);
			//amount += sampleAmount;
		}
		else
		{
			colour = colour + AA[i];
			raysFired++;
		}
	}

	colour = (colour + _Colour);
	colour = colour/ (raysFired + 1); //averages colours

	return colour;
}

glm::vec3 Tracer::AARandom(Ray _ray, int _index)
{
	//fires rays for addtional sampling using random sampling
	glm::vec3 colour = glm::vec3(0, 0, 0);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);
	float temp = dist(rng);

	switch (_index) //does it per quarter
	{
	case 0:
		for (int i = 0; i < sampleAmount; i++)
		{
			glm::vec2 one = glm::vec2(_ray.pix.x - (0.5 - (dist(rng) / 100.0f)), _ray.pix.y - (0.5 - (dist(rng) / 100.0f)));
			colour = colour + colourReturnAA(camera.rayCast(one));
			raysFired++;
		}
		break;
	case 1:
		for (int i = 0; i < sampleAmount; i++)
		{
			glm::vec2 two = glm::vec2(_ray.pix.x + (0.5 - (dist(rng) / 100.0f)), _ray.pix.y - (0.5 - (dist(rng) / 100.0f)));
			colour = colour + colourReturnAA(camera.rayCast(two));
			raysFired++;
		}
		break;
	case 2:
		for (int i = 0; i < sampleAmount; i++)
		{
			glm::vec2 three = glm::vec2(_ray.pix.x + (0.5 - (dist(rng) / 100.0f)), _ray.pix.y + (0.5 - (dist(rng) / 100.0f)));
			colour = colour + colourReturnAA(camera.rayCast(three));
			raysFired++;
		}
		break;
	case 3:
		for (int i = 0; i < sampleAmount; i++)
		{
			glm::vec2 four = glm::vec2(_ray.pix.x - (0.5 - (dist(rng) / 100.0f)), _ray.pix.y + (0.5 - (dist(rng) / 100.0f)));
			colour = colour + colourReturnAA(camera.rayCast(four));
			raysFired++;
		}
		break;
	default:
		std::cout << "No Case!?!?!?" << std::endl;
		break;
	}

	//random for entire pixel

	//float temp = dist(rng);
	/*for (int i = 0; i < sampleAmount; i++) 
	{
		glm::vec2 one = glm::vec2(_ray.pix.x - (1 - (dist(rng)/  100.0f)), _ray.pix.y - (1 - (dist(rng) / 100.0f)));
		glm::vec2 two = glm::vec2(_ray.pix.x + (1 - (dist(rng) / 100.0f)), _ray.pix.y - (1 - (dist(rng) / 100.0f)));
		glm::vec2 three = glm::vec2(_ray.pix.x + (1 - (dist(rng) / 100.0f)), _ray.pix.y + (1 - (dist(rng) / 100.0f)));
		glm::vec2 four = glm::vec2(_ray.pix.x - (1 - (dist(rng) / 100.0f)), _ray.pix.y + (1 - (dist(rng) / 100.0f)));

		colour = colour + colourReturnAA(camera.rayCast(one));
		colour = colour + colourReturnAA(camera.rayCast(two));
		colour = colour + colourReturnAA(camera.rayCast(three));
		colour = colour + colourReturnAA(camera.rayCast(four));
		raysFired = raysFired + 4;
	}*/

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

	return colour * 255.0f;
}

glm::vec3 Tracer::colourReturnAA(Ray _ray) //stops addtional calls of Anti Aliasing
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
