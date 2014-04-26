#include "application.h"
#include "utils.h"
#include "image.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//here add your init stuff
}

//render one frame
void Application::render(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render grid
	Image img( 400, 300);
	for (unsigned int x = 0; x < img.width; x++) {
		for(unsigned int y = 0; y < img.height; y++)
		{
			// Pantalla de joc (marge blanc)
			if (x > img.width/4 && x < 3*(img.width/4))
				img.setPixel(x, y, Color::WHITE );
	
			// Funció acceleració
			// unsigned int posBolaY = 80 + 150 * time + 0.5 * (-50) * time * time;
			
			// Funció Moviment Harmonic Simple
			unsigned int amplitud = 75;
			unsigned int frequencia = 4;
			unsigned int relativa = 135;

			unsigned int posBolaY = relativa + ( amplitud * cos(frequencia*time) );			

			// Quadrat vermell
			if (x > posBolaX - 10  &&  x < posBolaX + 10  &&  y > posBolaY - 10  &&  y < posBolaY + 10)
				img.setPixel(x, y, Color::RED );
		
		}
	}

	img.scale( this->window_width, this->window_height );

	renderImage( &img );

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

//called after render
void Application::update(double seconds_elapsed)
{
	if (keystate[SDL_SCANCODE_SPACE])
	{
		//...
	}
}

//keyboard press event 
void Application::onKeyPressed( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: exit(0); break; //ESC key, kill the app

		case SDLK_RIGHT:
			if ( posBolaX < 290 )	posBolaX += 5;			
			break;

		case SDLK_LEFT:
			if ( posBolaX > 110 )	posBolaX -= 5;
			break;
	}
}

//mouse button event
void Application::onMouseButton( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
