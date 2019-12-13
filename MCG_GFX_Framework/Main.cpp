
#include <cmath>

#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Tracer.h"
#include <iostream>



int main( int argc, char *argv[] )
{
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


	// Draws a single pixel at the specified coordinates in the specified colour!
	//MCG::DrawPixel( pixelPosition, pixelColour );

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();





	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:

	
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		Camera camera;
		Tracer tracer;
		/*tracer.addSphere(glm::vec3(320, 240, -15.0f), 30.0f);
		tracer.addSphere(glm::vec3(420, 240, -15.0f), 30.0f);*/
		tracer.addSphere(glm::vec3(0, 0, -15.0f), 1.0f);
		tracer.addLight(glm::vec3(-10, 0, 10.0f), glm::vec3(0.5, 1, 0.5));
		tracer.addCamera(camera);

		for (int x = 0; x < windowSize.x; x++)
		{
			for (int y = 0; y < windowSize.y; y++)
			{
				MCG::DrawPixel(glm::ivec2(x,y),
					tracer.colourReturn(camera.rayCast(glm::vec2(x,y))));
			}
		}
		//
		// Draw the pixel to the screen
		//MCG::DrawPixel( pixelPosition, pixelColour );
		std::cout << "end of frame" << std::endl;
	}

	return 0;
	

}
