/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the application, is in charge of creating the data,
	getting the user input, process the update and render.
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "includes.h"
#include "framework.h"
#include "image.h"
#include "obstacle.h"

class Application
{
public:

	/* VARIABLES */
	// Variable incorporada per tenir la posició horitzontal del quadrat vermell
	unsigned int posBolaX = 200;
	unsigned int posBolaY = 45;
	float vel = 0;

	unsigned int N_Obs = 12;

	unsigned int i, j;
	unsigned int distance;

	bool goDown = false;

	// Obstacles
	Obstacle arrayObs[12];

	/* FUNCTIONS */
	void mhsPlayer(void);				// getting posBolaY updated
	bool areEqual(Color c1, Color c2);	// comparing the color of two pixels



	//window
	SDL_Window* window;
	float window_width;
	float window_height;

	float time;

	//keyboard state
	const Uint8* keystate;

	//mouse state
	int mouse_state; //tells which buttons are pressed
	Vector2 mouse_position; //last mouse position
	Vector2 mouse_delta; //mouse movement in the last frame

	//constructor
	Application(const char* caption, int width, int height);

	//main methods
	void init( void );
	void render( void );
	void update( double dt );

	//methods for events
	void onKeyPressed( SDL_KeyboardEvent event );
	void onMouseButton( SDL_MouseButtonEvent event );

	//other methods to control the app
	void setWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 getWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(w,h);
	}

	void start();
};

#endif
