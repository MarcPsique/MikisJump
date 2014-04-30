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
	
	// Inicialitzem els parametres aleatoris del array de 12 obstacles que trobem en "application.h"
	arrayObs[0] = Obstacle(190, 20);

	for (i = 1; i < N_Obs; i++)	{
		unsigned int X = 260 - (rand() % 160);
		unsigned int Y = 25 * i +  (rand() % 15);
		arrayObs[i] = Obstacle(X, Y);
	}
}

//render one frame
void Application::render(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render grid
	Image img(400, 300);


	// Cada cop que ens trobem en (0,0) intento monitoritzar els diferents calculs de totes les posicions
	// i aixi despres imprimir la imatge d'una tirada.

	// Controla el moviment vertical del 'player' actualitzant la seva posicio posBolaY i la velocitat
	mhsPlayer();

	// En cas d'haver trobat una colisio, goDown es 1 i baixem tots els obstacles 'distance' en pixels
	if (goDown)
	for (i = 0; i < N_Obs; i++)
		arrayObs[i].updateObs(distance);

	// goDown es posa a fals sempre per a continuacio mirar si es produira una colisio
	goDown = false;

	// Si la velocitat es negativa (el player esta baixant), necessitem mirar si esta aprop d'algun obstacle.
	// Ho podem fer tal i com esta o be utilitzant lo de areEqual()
	if (vel < 0) {
		for (i = 0; i < N_Obs; i++)
		{
			if (posBolaX > arrayObs[i].getX() && posBolaX < arrayObs[i].getX() + 40 && posBolaY > arrayObs[i].getY() && posBolaY < arrayObs[i].getY() + 8)
			{
				goDown = true;
				distance = img.height - (img.height - arrayObs[i].getY()) + 20;
			}
		}
	}

	unsigned int x;
	unsigned int y;

	//fons blanc
	for (x = img.width / 4; x < 3 * (img.width / 4); x++)
		for (y = 0; y < img.height; y++)
			img.setPixel(x, y, Color::WHITE);

	// Imprimir el quadrat vermell o 'player' de 10 x 10
	for (x = posBolaX; x < posBolaX + 10; x++)
		for (y = posBolaY; y < posBolaY + 10; y++)
			img.setPixel(x, y, Color::RED);

	for (unsigned int x = 0; x < img.width; x++) {
		for(unsigned int y = 0; y < img.height; y++)
		{		

			// Com podem fer per imprimir els obstacles i que no es perdi temps recorrent-los tots en cada
			// iteracio, aixo realment es el que fa que vagi molt lent ja que perdem massa temps imprimint
			// cada pixel fen les comparacions d'aqui abaix.
			// El nostre objectiu es que tot el temps de delay estigui a la primera iteracio (x=0 && y=0)
			for (i = 0; i < N_Obs; i++)			
				if (x > arrayObs[i].getX() && x < arrayObs[i].getX() + 40 && y > arrayObs[i].getY() && y < arrayObs[i].getY() + 5)
					img.setPixel(x, y, Color::BLUE);					

		}
	}

	img.scale( this->window_width, this->window_height );

	renderImage( &img );

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

/************
 * FUNCTIONS *
 ************/
// Funcio Moviment Harmonic Simple (desplaçament vertical)
// Actualitzem la posició posBolaY i la velocitat (derivada posBolaY) que la utilitzem per definir que quan
// aquesta sigui negativa es quan volem baixar els obstacles. Si es positiva el 'player' estará pujant cap amunt.
void Application::mhsPlayer(void)
{
	// relativa = 100;	// amplitud = 80;	// frequencia = 4;
	// (min)20 - 100 - 180(max)
	float consFase = (4 * time) - (PI / 2);
	posBolaY = 100 + (80 * sin(consFase));
	vel = 4 * 80 * cos(consFase);
}


//comparing the color of two pixels
bool Application::areEqual(Color c1, Color c2)
{
	if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
		return true;
	else
		return false;
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
