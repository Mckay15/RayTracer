#include "Collision.h"
#include "Ray.h"
#include "Sphere.h"
#include <iostream>

glm::vec3 Collision::intersectNormal(Ray _ray, Sphere _sphere)
{
	glm::vec3 hitN = glm::normalize(hitPoint(_ray) - _sphere.centre); 
	return hitN;  //finds normal from hitpoint and normalizes it
}
glm::vec3 Collision::hitPoint(Ray _ray)
{
	glm::vec3 hitP = _ray.origin + _ray.driection * t;
	return hitP;     //works out hitpoint from the sphere's intersection
}
bool Collision::sphereIntersect(Ray _ray, Sphere _sphere)
{
	glm::vec3 v = _ray.origin - _sphere.centre;

	float a = glm::dot(_ray.driection, _ray.driection);  
	float b = 2 * glm::dot(v, _ray.driection);
	float c = glm::dot(v, v) - _sphere.radius * _sphere.radius;

	float delta = b * b - 4 * a * c;

	if (delta <= 0.0f)
	{
		return false;  //checks if valid
	}

	float t1 = (-b - glm::sqrt(delta)) / 2;
	float t2 = (-b + glm::sqrt(delta)) / 2;

	if (t1 > t2)
	{
		t = t2;
		return true;  //checks where camera is in relation to sphere
	}

	t = t1;

	return true;
}