#pragma once
#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include <vector>

class Camera
{
public:
	Ray rayCast(glm::ivec2 _pix);
	Ray rayCastOther(glm::vec2 _pix);
	void Init(glm::ivec2 _windowSize);
	Camera();
	~Camera();
	glm::mat4 viewMatrix();
	glm::vec3 antialiasing();
	//Ray getRay(int _x, int _y);
private:
	glm::mat4 perp();
	//std::vector<std::vector<Ray>> rays;
	//Ray rayContainer[400][400];
	glm::vec2 windowSize;
	float IAR;
	glm::vec3 pos = glm::vec3(320, 240, 0);
};