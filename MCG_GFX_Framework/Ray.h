#pragma once
#include <GLM/glm.hpp>

class Ray
{
public:
	void init(glm::vec3 _point, glm::vec3 _direction);
	glm::vec3 origin;
	glm::vec3 driection = glm::vec3(0,0,1);
};