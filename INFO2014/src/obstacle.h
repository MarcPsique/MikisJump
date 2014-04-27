#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "includes.h"
#include "framework.h"

class Obstacle
{
	unsigned int posObsX;
	unsigned int posObsY;

public:

	// Constructor
	Obstacle();
	Obstacle(unsigned int X, unsigned int Y);

	// Getters
	unsigned int getX(void);
	unsigned int getY(void);

	// Setters
	void setX(unsigned int X);
	void setY(unsigned int Y);


};

#endif
