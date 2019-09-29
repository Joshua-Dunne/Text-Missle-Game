#pragma once
#include "Position.h"


typedef struct Enemy
{
	Enemy();
	Enemy(int coordX, int coordY);
	Coordinates coordinates;
	bool alive = true;

}Target;

