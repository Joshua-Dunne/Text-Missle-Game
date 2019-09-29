#pragma once
#include "Enemy.h"
#include "Position.h"

struct Missle
{
	enum WarHead { EXPLOSIVE, NUCLEAR };

	WarHead payload;
	Coordinates coordinates;
	Target target;
	bool armed = false;
	int explosiveCode = 1234;
	int nuclearCode = 2345;
	int userCode = 0;

	void choosePayload()
	{
		int choice = 2;

		while (choice != 0 && choice != 1)
		{
			std::cout << "Please choose a Warhead. 0 Explosive, 1 Nuclear: ";
			std::cin >> choice;

			if (choice != 0 && choice != 1)
			{
				std::cout << "Incorrect choice given." << std::endl << std::endl;
			}
		}

		payload = static_cast<WarHead>(choice);
		coordinates.x = 1;
		coordinates.y = 1;
	}

	void inputCode()
	{
		std::cout << "Please enter code for ";
		if (payload == WarHead::EXPLOSIVE)
			std::cout << "explosive ";
		else
			std::cout << "nuclear ";

		std::cout << "drone: " << std::endl;

		std::cin >> userCode;

		arm();
	}

	void arm()
	{
		if (payload == WarHead::EXPLOSIVE)
		{
			if (userCode == explosiveCode)
				armed = true;
			else
			{
				armed = false;
				std::cout << "Drone Error! Wrong Code given. Bombs will be unarmed!!" << std::endl;
			}
		}
		else if (payload == WarHead::NUCLEAR)
		{
			if (userCode == nuclearCode)
				armed = true;
			else
			{
				armed = false;
				std::cout << "Drone Error! Wrong Code given. Bombs will be unarmed!!" << std::endl;
			}
		}
		else
		{
			std::cout << "Explosive choice incorrect." << std::endl;
		}
		

	}

	void choosePosition()
	{
		coordinates.x = 0;
		coordinates.y = 0;
		int choiceX = -1;
		int choiceY = -1;

		while (choiceX < 0 || choiceX > 10)
		{
			std::cout << "Drones can go to a Max of 10X and 10Y, and min of 0X, 0Y." << std::endl;
			std::cout << "Please take care to not go outside the range." << std::endl;
			std::cout << "Please enter X Co-ordinate: ";
			std::cin >> choiceX;
			std::cout << std::endl;
			std::cout << "Please enter y Co-ordinate: ";
			std::cin >> choiceY;
			std::cout << std::endl;
		}
		

		target.coordinates.x = choiceX;
		target.coordinates.y = choiceY;
	}

	void update(Target t_enemies[], int const t_MAX_ENEMIES)
	{
		while (coordinates.x != target.coordinates.x ||
			coordinates.y != target.coordinates.y)
		{
			if (coordinates.x != target.coordinates.x)
			{
				coordinates.x++;
			}

			if (coordinates.y != target.coordinates.y)
			{
				coordinates.y++;
			}

			checkCollision(t_enemies, t_MAX_ENEMIES);
			// we only want to check final collision once we reach out target location
			// so i made the drone stick 1 behind the intended location
			// so we can check that final collision later on
		}

		if (coordinates.x == target.coordinates.x)
		{
			if (coordinates.y == target.coordinates.y)
			{
				std::cout << std::endl << "Location reached, attacking..." << std::endl;
				checkCollision(t_enemies, t_MAX_ENEMIES);
				std::cout << "Attack finished. Returning to base." << std::endl;;
				std::cout << std::endl;
			}
		}

	}

	void checkCollision(Target t_enemies[], int const t_MAX_ENEMIES)
	{
		for (int i = 0; i < t_MAX_ENEMIES; i++)
		{
			if (t_enemies[i].alive)
			{
				if (coordinates.x == t_enemies[i].coordinates.x)
				{
					if (coordinates.y == t_enemies[i].coordinates.y)
					{
						std::cout << "Enemy hit at" << t_enemies[i].coordinates.x << ", "
							<< t_enemies[i].coordinates.y << std::endl;
						t_enemies[i].alive = false;
					}
				}
			}
		}
	}
};

