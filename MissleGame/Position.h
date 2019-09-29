#pragma once
#include <iostream>

typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}
}Coordinates;

