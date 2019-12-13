#pragma once
#include <GLM/glm.hpp>
#include "Ray.h"
#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"

class Tracer
{
private:
	glm::vec3 background = glm::vec3(250,0,0);
	std::vector<Sphere> objects;
	std::vector<Light> lights;
	Camera camera;
public:
	void addSphere(glm::vec3 _centre, float _radius);
	void addLight(glm::vec3 _pos, glm::vec3 _colour);
	void addCamera(Camera _camera);
	glm::vec3 colourReturn(Ray _ray);
};