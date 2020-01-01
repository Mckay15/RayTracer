#pragma once
#include <GLM/glm.hpp>
#include <vector>
#include "Light.h"

class Camera;
class Ray;
class Sphere;

class Tracer
{
private:
	glm::vec3 background = glm::vec3(250,0,0);
	std::vector<Sphere> objects;
	std::vector<Light> lights;
	Camera *camera;
	std::vector<Ray> rays;
	int tol = 5;
	glm::vec3 AARandom(Ray _ray);
	glm::vec3 AA[4];
public:
	void addSphere(glm::vec3 _centre, float _radius);
	void addLight(glm::vec3 _pos, glm::vec3 _colour);
	void addCamera(Camera* _camera);
	glm::vec3 colourReturn(Ray _ray);
	glm::vec3 colourReturnAA(Ray _ray);
	glm::vec3 AntiAliasing(Ray _ray, glm::vec3 _colour);
	Tracer();
	~Tracer();
};