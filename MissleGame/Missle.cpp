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
		std::cout << "Explosives will destroy anything the Drone goes over." << std::endl;
		std::cout << "Nuclear will only destroy the target location,";
		std::cout << " but it will also destroy surrounding areas." << std::endl << std::endl;
		std::cout << "You have " << numberOfExplosives << " explosives remaining." << std::endl;
		std::cout << "You have " << numberOfNuclears << " nukes remaining." << std::endl;

		while (choice != 0 && choice != 1)
		{ // make sure the player only choose 0 or 1
			std::cout << "Please choose a Warhead. 0 Explosive, 1 Nuclear: ";
			std::cin >> choice;

			if (choice != 0 && choice != 1)
			{
				std::cout << "Incorrect choice given." << std::endl << std::endl;
			}

			if (choice == static_cast<int>(WarHead::EXPLOSIVE)
				&& numberOfExplosives == 0)
			{
				std::cout << "No Explosive Warheads left." << std::endl << std::endl;
				noRemainingWarheads = true;
			}

			if (choice == static_cast<int>(WarHead::NUCLEAR)
				&& numberOfNuclears == 0)
			{
				std::cout << "No Nuclear Warheads left." << std::endl << std::endl;
				noRemainingWarheads = true;
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
	if (payload == WarHead::EXPLOSIVE) // when the player chose explosive warheads
	{
		if (userCode == explosiveCode) // check to make sure they put in the right code
		{
			armed = true;
			numberOfExplosives--;
		}
		else
		{
			armed = false;
			std::cout << "Drone Error! Wrong Code given. Bombs will be unarmed!!" << std::endl;
		}
	}
	else if (payload == WarHead::NUCLEAR) // if the player chose nuclear
	{
		if (userCode == nuclearCode) // check to make sure they put in the right code
		{
			armed = true;
			numberOfNuclears--;
		}
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
	// reset drone's position for next potential move
	coordinates.x = 0;
	coordinates.y = 0;

	int choiceX = -1;
	int choiceY = -1;

	std::cout << "Drones can go to a Max of 10X and 10Y, and min of 0X, 0Y." << std::endl;
	std::cout << "Please take care to not go outside the range." << std::endl;
	std::cout << "Please enter X Co-ordinate: ";
	std::cin >> choiceX;
	std::cout << std::endl;
	std::cout << "Please enter y Co-ordinate: ";
	std::cin >> choiceY;
	std::cout << std::endl;

	target.coordinates.x = choiceX; // set the target's x and y
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
		coordinates.y != target.coordinates.y) // make sure the drone doesn't go outside the range
	{
		if ((coordinates.x <= 10 && coordinates.y <= 10)
			&& (target.coordinates.x >= 0 && target.coordinates.y >= 0))
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
		else
		{
			std::cout << "**************************************************" << std::endl;
			std::cout << "Drone went outside of range. Bombs disarmed. Returning to base..." << std::endl;
			std::cout << "**************************************************" << std::endl << std::endl;
			armed = false;
			break;
		}
		
	}

	if (coordinates.x == target.coordinates.x && armed)
	{
		if (coordinates.y == target.coordinates.y && armed)
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
	if (payload == WarHead::EXPLOSIVE && armed)
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

	if (payload == WarHead::NUCLEAR && armed)
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
						// check the area we're attacking first
						if (t_enemies[i].coordinates.x == target.coordinates.x
							&& t_enemies[i].coordinates.y == target.coordinates.y)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}

						// then check surrounding areas
						if (t_enemies[i].coordinates.x == target.coordinates.x + 1
							|| t_enemies[i].coordinates.x == target.coordinates.x - 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}

						if (t_enemies[i].coordinates.y == target.coordinates.y + 1
							|| t_enemies[i].coordinates.y == target.coordinates.y - 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}
					}

					if (t_friendlies[i].alive)
					{
						// check the area we're attacking first
						if (t_friendlies[i].coordinates.x == target.coordinates.x
							&& t_friendlies[i].coordinates.y == target.coordinates.y)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}

						// then check surrounding areas
						if (t_friendlies[i].coordinates.x == target.coordinates.x + 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.x == target.coordinates.x - 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}

						if (t_friendlies[i].coordinates.y == target.coordinates.y + 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.y == target.coordinates.y - 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
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
