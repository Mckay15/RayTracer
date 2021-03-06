#include "Camera.h"
#include "Ray.h"

Ray Camera::rayCast(glm::ivec2 _pix) // function creates ray in perspective
{
	Ray ray;      
	float px = ((2.0f * (float)_pix.x) / ((float)windowSize.x)) - 1.0f;
	float py = -((2.0f * (float)_pix.y) / ((float)windowSize.y)) + 1.0f;
	//ray.init(_pix, glm::vec2(screenWidth, screenHeight));
	glm::vec4 near = glm::vec4(px, py, -1, 1);
	glm::vec4 far = glm::vec4(px, py, 1, 1);
	near = perspectiveMat * near;
	far = perspectiveMat * far;
	near /= near.w;
	far /= far.w;
	near = view * near;
	far = view * far;
	glm::vec3 dir = glm::normalize(far - near);
	glm::vec3 pos = near;
	ray.init(pos, dir, _pix);
	//rayContainer[_pix.x][_pix.y] = ray;
	//rays[_pix.y][_pix.x] = ray;
	return ray;
}


glm::mat4 Camera::perp()
{
	glm::mat4 perjection = glm::perspective(glm::radians(45.0f), (windowSize.x / windowSize.y), 1.0f, 150.0f);
	return perjection;
}

glm::mat4 Camera::viewMatrix()
{
	glm::mat4 view = glm::mat4(1);//glm::lookAt(glm::vec3(0, 0, 10), pos, glm::vec3(0, 1, 0));
	return view;
}

void Camera::Init(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;
	perspectiveMat = glm::inverse(glm::perspective(glm::radians(45.0f), (windowSize.x / windowSize.y), 1.0f, 150.0f));
	view = glm::inverse(glm::mat4(1));
}

Camera::Camera()
{
	
}

Camera::~Camera()
{
}

//OLD CODE

//Ray Camera::rayCastOther(glm::vec2 _pix)
//{
//	Ray ray;
//	float px = ((2.0f * (float)_pix.x) / ((float)windowSize.x)) - 1.0f;
//	float py = -((2.0f * (float)_pix.y) / ((float)windowSize.y)) + 1.0f;
//	//ray.init(_pix, glm::vec2(screenWidth, screenHeight));
//	glm::vec4 near = glm::vec4(px, py, -1, 1);
//	glm::vec4 far = glm::vec4(px, py, 1, 1);
//	near = perspectiveMat * near;
//	far = perspectiveMat * far;
//	near /= near.w;
//	far /= far.w;
//	near = view * near;
//	far = view * far;
//	glm::vec3 dir = glm::normalize(far - near);
//	glm::vec3 pos = near;
//	ray.init(pos, dir, _pix);
//	//rayContainer[_pix.x][_pix.y] = ray;
//	return ray;
//}

//Ray Camera::getRay(int _x, int _y)
//{
//	return rays[_y][_x];
//}