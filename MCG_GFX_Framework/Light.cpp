#include "Light.h"

Light::Light(glm::vec3 _pos, glm::vec3 _colour)
{
	origin = _pos;
	lightColour = _colour;
}

Light::~Light()
{
}
