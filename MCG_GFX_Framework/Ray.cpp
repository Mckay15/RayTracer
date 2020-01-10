#include "Ray.h"

void Ray::init(glm::vec3 _point, glm::vec3 _direction, glm::ivec2 _pix)
{
	pix = _pix;
	origin = _point;
	driection = _direction;
}