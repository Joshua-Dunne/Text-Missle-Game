#include "Enemy.h"

Enemy::Enemy()
{
	coordinates.x = rand() % 8 + 1;
	coordinates.y = rand() % 8 + 1;
}

Enemy::Enemy(int coordX, int coordY)
{
	coordinates.x = coordX;
	coordinates.y = coordY;
}