#pragma once
#include <GLM/glm.hpp>

class Ray;
class Sphere;

class Collision
{
public:
	glm::vec3 intersectNormal(Ray _ray, Sphere _sphere);
	glm::vec3 hitPoint(Ray _ray);
	bool sphereIntersect(Ray _ray, Sphere _spher);
private:
	float t = 0.0f;
	
};