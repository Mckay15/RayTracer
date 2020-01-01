#pragma once
#include <GLM/glm.hpp>

class Ray;
class Light;
class Camera;

class Sphere
{
public:
	float t;
	glm::vec3 shadePixel(Ray _ray, glm::vec3 _inter, Light _light, Camera *_camera);
	glm::vec3 shadePixelNormal(Ray _ray, glm::vec3 _inter, Light _light, Camera *_camera);
	glm::vec3 centre;
	glm::vec3 materialColour = glm::vec3(1, 0, 0);
	float radius;
	Sphere(glm::vec3 _centre, float _radius);
	~Sphere();
};