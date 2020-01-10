#pragma once
#include "MCG_GFX_Lib.h"

class Light //holds light informaiton
{
public:
	glm::vec3 lightColour = glm::vec3(1, 1, 1);
	glm::vec3 origin = glm::vec3(0, 0, 0);
	glm::vec3 intensity = glm::vec3(0.8, 0.8, 0.8);
	Light(glm::vec3 _pos, glm::vec3 _colour);
	~Light();
};