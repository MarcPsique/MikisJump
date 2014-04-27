#include "includes.h"
#include "framework.h"
#include "obstacle.h"


// Constructors
Obstacle::Obstacle() {}

Obstacle::Obstacle (unsigned int X, unsigned int Y)
{
	this->posObsX = X;
	this->posObsY = Y;
}

// Getters
unsigned int Obstacle::getX (void)		{ return this->posObsX; }
unsigned int Obstacle::getY (void)		{ return this->posObsY; }

// Setters
void Obstacle::setX (unsigned int X)		{ this->posObsX = X; }
void Obstacle::setY (unsigned int Y)		{ this->posObsY = Y; }