
#include <cmath>

#include <exception>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Tracer.h"
#include "ThreadHolder.h"
#include <future>
#include <iostream>
#include <thread>

void threadCreation(int _yChange, glm::ivec2 _windowSize, Tracer _tracer, Camera _camera, int _i);

int main( int argc, char *argv[] )
{
	static const int threadCount = 2;
	int frame = 0;
	//std::vector<std::thread> threads;
	//std::thread threadObj[threadCount];
	// Variable for storing window dimensions
	glm::ivec2 windowSize( 640, 480 );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground( glm::ivec3(0,0,0) );

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::ivec3 pixelColour( 255, 0, 0 );

	Camera camera;
	camera.Init(windowSize);
	Tracer tracer;
	// Draws a single pixel at the specified coordinates in the specified colour!
	//MCG::DrawPixel( pixelPosition, pixelColour );

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();

	//for (int y = 0; y < windowSize.y; y++)
	//{
	//	for (int x = 0; x < windowSize.x; x++)
	//	{
	//		camera.rayCast(glm::vec2(x, y));
	//	}
	//}

	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:
	tracer.addSphere(glm::vec3(0, -50.0f, -15.0f), 50.0f);
	tracer.addSphere(glm::vec3(0, 0, -15.0f), 3.0f);
	tracer.addSphere(glm::vec3(5, -2, -15.0f), 3.0f);
	tracer.addLight(glm::vec3(10, 0, 10.0f), glm::vec3(1, 1, 1));
	tracer.addCamera(&camera);
	int yCoordChange = windowSize.y / threadCount;
	
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		//threads.clear();
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		/*tracer.addSphere(glm::vec3(320, 240, -15.0f), 30.0f);
		tracer.addSphere(glm::vec3(420, 240, -15.0f), 30.0f);*/
	
		std::size_t max = windowSize.x * windowSize.y;
		std::size_t cores = std::thread::hardware_concurrency();
		volatile std::atomic<std::size_t> count(0);
		std::vector<std::future<void>> future_vector;


		//for (std::size_t i(0); i < cores; ++i)
		//	future_vector.emplace_back(std::async([=, &tracer, &camera]()
		//{
		//	for (std::size_t index(i); index < max; index += cores)
		//	{
		//		std::size_t x = i % windowSize.x;
		//		std::size_t y = i / windowSize.x;
		//		MCG::DrawPixel(glm::ivec2(x, y),
		//		tracer.colourReturn(camera.rayCast(glm::vec2(x, y))));
		//	}
		//}));
		//future_vector.back().wait();
		//while (cores--)
		//	future_vector.emplace_back(
		//		std::async([=, &tracer, &camera, &count]()
		//	{
		//		while (true)
		//		{
		//			std::size_t i = count++;
		//			if (i >= max)
		//			{
		//				break;
		//			}
		//			std::size_t x = i % windowSize.x;
		//			std::size_t y = i / windowSize.x;

		//			MCG::DrawPixel(glm::ivec2(x, y),
		//			tracer.colourReturn(camera.rayCast(glm::vec2(x, y))));
		//		}
		//	}));

		for (int y = 0; y < windowSize.y; y++)
		{
			for (int x = 0; x < windowSize.x; x++)
			{
				MCG::DrawPixel(glm::ivec2(x, y),  //glm::vec3(250, 1, 1));
					tracer.colourReturn(camera.rayCast(glm::vec2(x, y))));
			}
		}

		//for (int i = 1; i <= threadCount; i++)
		//{
		//	//auto fut = std::async(std::launch::async, threadCreation, yCoordChange, windowSize, tracer, camera, i);
		//	//threads.push_back(std::thread(threadCreation, yCoordChange, windowSize, tracer, camera, i));
		//	//threads[i - 1].join();
		//	//threadObj[i - 1].join();
		//}

		//
		// Draw the pixel to the screen
		//MCG::DrawPixel( pixelPosition, pixelColour );
		std::cout << "end of frame " << frame++ <<" " << cores << std::endl;
	}

	return 0;
}

void threadCreation(int _yChange, glm::ivec2 _windowSize, Tracer _tracer, Camera _camera, int _i)
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
