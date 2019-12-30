#pragma once
#include "MCG_GFX_Lib.h"

class Tracer;
class Camera;

class ThreadHolder
{
public:
	void ThreadHolder::threadCreation(int _yChange, glm::ivec2 _windowSize, Tracer _tracer, Camera _camera, int _i);

};
