#include "ThreadHolder.h"
#include "Tracer.h"
#include "Camera.h"

void ThreadHolder::threadCreation(int _yChange, glm::ivec2 _windowSize, Tracer _tracer, Camera _camera, int _i)
{
	for (int y = 0; y < _yChange * _i; y++)
	{
		for (int x = 0; x < _windowSize.x; x++)
		{
			MCG::DrawPixel(glm::ivec2(x, y),
				_tracer.colourReturn(_camera.rayCast(glm::vec2(x, y))));
		}
	}
}