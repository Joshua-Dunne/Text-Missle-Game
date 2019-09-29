#include "Missle.h"

/// <summary>
/// Get the Player to choose a Warhead.
/// </summary>
void Missle::choosePayload()
{
	{
		int choice = 2;

		std::cout << "Each Payload has a launch code. This code is needed to arm the payload." << std::endl;
		std::cout << "Please refer to your manual for the launch codes." << std::endl;

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
}

/// <summary>
/// Check to see if the Player puts in the right code to arm it.
/// Explosive: 1234
/// Nuclear: 2345
/// </summary>
void Missle::inputCode()
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

/// <summary>
/// Arm the Payload if the correct code was given
/// </summary>
void Missle::arm()
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

/// <summary>
/// Choose where the drone will go.
/// </summary>
void Missle::choosePosition()
{
	coordinates.x = 0;
	coordinates.y = 0;
	int choiceX = -1;
	int choiceY = -1;

	while (choiceX < 0 || choiceX > 10 && choiceY < 0 || choiceY > 10)
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

/// <summary>
/// Update the Drone's position, and attack any potential targets.
/// Explosive blows up anything in it's path.
/// Nuclear blows up the Target area and surrounding areas.
/// </summary>
/// <param name="t_enemies">Array of Enemies</param>
/// <param name="t_friendlies">Array of Friendlies</param>
/// <param name="t_MAX_TARGETS">Max number of enemies/friendlies</param>
void Missle::update(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS)
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

		checkCollision(t_enemies, t_friendlies, t_MAX_TARGETS);
	}

	if (coordinates.x == target.coordinates.x)
	{
		if (coordinates.y == target.coordinates.y)
		{
			std::cout << "Attack finished. Returning to base." << std::endl;;
			std::cout << std::endl;
		}
	}

}

/// <summary>
/// See if the Drone has passed by anything, or if the drone has hit anything in an area.
/// Explosive blows up anything in it's path.
/// Nuclear blows up the Target area and surrounding areas.
/// </summary>
/// <param name="t_enemies"></param>
/// <param name="t_friendlies"></param>
/// <param name="t_MAX_ENEMIES"></param>
void Missle::checkCollision(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS)
{
	if (payload == WarHead::EXPLOSIVE)
	{
		for (int i = 0; i < t_MAX_TARGETS; i++)
		{
			// check to see if the enemy we are attacking is alive first
			if (t_enemies[i].alive)
			{
				if (coordinates.x == t_enemies[i].coordinates.x)
				{
					if (coordinates.y == t_enemies[i].coordinates.y)
					{
						std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
							<< t_enemies[i].coordinates.y << std::endl;
						t_enemies[i].alive = false;
					}
				}
			}

			// check to see if the friendly we are attacking is alive first
			if (t_friendlies[i].alive)
			{
				if (coordinates.x == t_friendlies[i].coordinates.x)
				{
					if (coordinates.y == t_friendlies[i].coordinates.y)
					{
						std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
							<< t_friendlies[i].coordinates.y << std::endl;
						t_friendlies[i].alive = false;
					}
				}
			}
		}
	}

	if (payload == WarHead::NUCLEAR)
	{
		if (coordinates.x == target.coordinates.x)
		{
			if (coordinates.y == target.coordinates.y)
			{
				std::cout << "Reached area. Dropping nuke..." << std::endl;
				for (int i = 0; i < t_MAX_TARGETS; i++)
				{
					if (t_enemies[i].alive)
					{
						if (t_enemies[i].coordinates.x == target.coordinates.x + 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}
						else if (t_enemies[i].coordinates.x == target.coordinates.x - 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}

						if (t_enemies[i].coordinates.y == target.coordinates.y + 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}
						else if (t_enemies[i].coordinates.y == target.coordinates.y - 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}
					}

					if (t_friendlies[i].alive)
					{
						if (t_friendlies[i].coordinates.x == target.coordinates.x + 1)
						{
							std::cout << "Enemy hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.x == target.coordinates.x - 1)
						{
							std::cout << "Enemy hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}

						if (t_friendlies[i].coordinates.y == target.coordinates.y + 1)
						{
							std::cout << "Enemy hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.y == target.coordinates.y - 1)
						{
							std::cout << "Enemy hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
					}
				}
			}
		}
	}
}
