#include "Sphere.h"
#include "Ray.h"
#include "Collision.h"
#include "Light.h"
#include "Camera.h"

Sphere::Sphere(glm::vec3 _centre, float _radius)
{
	centre = _centre;
	radius = _radius;
}

glm::vec3 Sphere::shadePixel(Ray _ray, glm::vec3 _inter, Light _light, Camera _camera)
{
	//glm::vec3 normal = _camera.viewMatrix() * glm::vec4(_inter, 0.0f);
	glm::vec3 lightPos = _camera.viewMatrix() * glm::vec4(_light.origin, 0.0f);
	glm::vec3 lightLocation = glm::normalize(lightPos - _inter);
	float a = glm::max(glm::dot(lightLocation, _inter),0.0f);
	glm::vec3 colour = _light.lightColour * a;
	glm::vec3 temp = colour * 255.0f;
	return temp;
}


Sphere::~Sphere()
{
}
