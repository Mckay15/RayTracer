#pragma once
#include "MCG_GFX_Lib.h"

class Ray;

class Camera
{
public:
	Ray rayCast(glm::vec2 _pix);
	Camera();
	~Camera();
	glm::mat4 viewMatrix();
	glm::vec3 antialiasing();
private:
	glm::mat4 perp();
	float screenWidth = 640;
	float screenHeight = 480;
	float IAR;
	glm::vec3 pos = glm::vec3(320, 240, 0);
};