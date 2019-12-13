#include "Ray.h"

void Ray::init(glm::vec3 _point, glm::vec3 _direction)
{
	origin = _point;
	driection = _direction;
}