#include "application.h"
#include "utils.h"
#include "image.h"
#include "obstacle.h"

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
	
	// Inicialitzem els parametres aleatoris del array de 17 obstacles que trobem en "application.h"
	// Despres els anirem modificant a mesura que avança el joc.
	unsigned int i;
	for (i = 0; i < 17; i++)
	{
		unsigned int X = 260 - (rand() % 160);	// 260 perque cada obstacle te una component hor. de 40 pixels
												// 160 perque es el marge blanc (la pantalla del joc)
		unsigned int Y = rand () % 20 + i*i;	// Aqui hem de trobar una funcio amb bona dispersio per que no
												// surtin obstacles en la mateixa y, estiguin dispersats per la pantalla.
		arrayObs[i] = Obstacle(X, Y);			// Inicialitzem l'array d'obstacles amb les posicions trobades
	}
}

//render one frame
void Application::render(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render grid
	Image img(400, 300);
	for (unsigned int x = 0; x < img.width; x++) {
		for(unsigned int y = 0; y < img.height; y++)
		{
			// Pantalla de joc (marge blanc)
			if (x > img.width/4 && x < 3*(img.width/4))
				img.setPixel(x, y, Color::WHITE );
	
			// Funcio Moviment Harmonic Simple (desplaçament vertical)
			// relativa = 125;	// amplitud = 80;	// frequencia = 4;
			unsigned int posBolaY = 125 + ( 80 * sin(4*time) );

			// Imprimir el quadrat vermell
			if (x > posBolaX  &&  x < posBolaX + 10  &&  y > posBolaY  &&  y < posBolaY + 10)
				img.setPixel(x, y, Color::RED );

			// Imprimir obstacles per la pantalla amb 40 pixels horitzontals i 5 d'alçada
			int i;
			for (i = 0; i < 17; i++) {
				if (x > arrayObs[i].getX() && x < arrayObs[i].getX() + 40 && y > arrayObs[i].getY() && y < arrayObs[i].getY() + 5)
					img.setPixel(x, y, Color::BLUE );
			}



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

		// Desplaçament horitzontal
		case SDLK_RIGHT:
			if ( posBolaX < 300 - 10 )	posBolaX += 10;
			else if (posBolaX == 290)	posBolaX = 100;
			break;
		case SDLK_LEFT:
			if ( posBolaX > 100 )		posBolaX -= 10;
			else if (posBolaX == 100)	posBolaX = 290;
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
