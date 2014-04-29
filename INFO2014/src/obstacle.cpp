#include "includes.h"
#include "framework.h"
#include "obstacle.h"

// Constructors
Obstacle::Obstacle() {}

Obstacle::Obstacle(unsigned int X, unsigned int Y)
{
	this->posObsX = X;
	this->posObsY = Y;
}

// Getters
unsigned int Obstacle::getX(void)		{ return this->posObsX; }
unsigned int Obstacle::getY(void)		{ return this->posObsY; }

// Setters
void Obstacle::setX(unsigned int X)	{ this->posObsX = X; }
void Obstacle::setY(unsigned int Y)	{ this->posObsY = Y; }

// Actualitza els obstacles
void Obstacle::updateObs(unsigned int distance)
{
	// Reiniciar la seva posició quan es trobin distant a menys de 20 pixels del marge inferior
	if (this->posObsY < 20)
	{
		this->posObsX = 260 - (rand() % 160);	// Nova X aleatoria
		this->posObsY += 275;					// Sumem 275 pixels a la Y del obstacle per que surti per dalt
	}

	this->posObsY -= distance;		// Actualitzem la posició del obstacle amb la distancia rebuda com a parametre
}
