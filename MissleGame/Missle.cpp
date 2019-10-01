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
		std::cout << "You have " << m_numberOfExplosives << " explosives remaining." << std::endl;
		std::cout << "You have " << m_numberOfNuclears << " nukes remaining." << std::endl;

		while (choice != 0 && choice != 1)
		{ // make sure the player only choose 0 or 1
			std::cout << "Please choose a Warhead. 0 Explosive, 1 Nuclear: ";
			std::cin >> choice;

			if (choice != 0 && choice != 1)
			{
				std::cout << "Incorrect choice given." << std::endl << std::endl;
			}

			if (choice == static_cast<int>(WarHead::EXPLOSIVE)
				&& m_numberOfExplosives == 0)
			{
				std::cout << "No Explosive Warheads left." << std::endl << std::endl;
				m_noRemainingWarheads = true;
			}

			if (choice == static_cast<int>(WarHead::NUCLEAR)
				&& m_numberOfNuclears == 0)
			{
				std::cout << "No Nuclear Warheads left." << std::endl << std::endl;
				m_noRemainingWarheads = true;
			}
		}

		m_payload = static_cast<WarHead>(choice);
		m_coordinates.x = 1;
		m_coordinates.y = 1;
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
	if (m_payload == WarHead::EXPLOSIVE)
		std::cout << "explosive ";
	else
		std::cout << "nuclear ";

	std::cout << "drone: " << std::endl;

	std::cin >> m_userCode;

	arm();
}

/// <summary>
/// Arm the Payload if the correct code was given
/// </summary>
void Missle::arm()
{
	if (m_payload == WarHead::EXPLOSIVE) // when the player chose explosive warheads
	{
		if (m_userCode == m_explosiveCode) // check to make sure they put in the right code
		{
			m_armed = true;
			m_numberOfExplosives--;
		}
		else
		{
			m_armed = false;
			std::cout << "Drone Error! Wrong Code given. Bombs will be unarmed!!" << std::endl;
		}
	}
	else if (m_payload == WarHead::NUCLEAR) // if the player chose nuclear
	{
		if (m_userCode == m_nuclearCode) // check to make sure they put in the right code
		{
			m_armed = true;
			m_numberOfNuclears--;
		}
		else
		{
			m_armed = false;
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
	m_coordinates.x = 0;
	m_coordinates.y = 0;

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

	m_target.coordinates.x = choiceX; // set the target's x and y
	m_target.coordinates.y = choiceY;
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
	while (m_coordinates.x != m_target.coordinates.x ||
		m_coordinates.y != m_target.coordinates.y) // make sure the drone doesn't go outside the range
	{
		if ((m_coordinates.x <= 10 && m_coordinates.y <= 10)
			&& (m_target.coordinates.x >= 0 && m_target.coordinates.y >= 0))
		{
			if (m_coordinates.x != m_target.coordinates.x)
			{
				m_coordinates.x++;
			}

			if (m_coordinates.y != m_target.coordinates.y)
			{
				m_coordinates.y++;
			}

			checkCollision(t_enemies, t_friendlies, t_MAX_TARGETS);
		}
		else
		{
			std::cout << "**************************************************" << std::endl;
			std::cout << "Drone went outside of range. Bombs disarmed. Returning to base..." << std::endl;
			std::cout << "**************************************************" << std::endl << std::endl;
			m_armed = false;
			break;
		}
		
	}

	if (m_coordinates.x == m_target.coordinates.x && m_armed)
	{
		if (m_coordinates.y == m_target.coordinates.y && m_armed)
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
	if (m_payload == WarHead::EXPLOSIVE && m_armed)
	{
		for (int i = 0; i < t_MAX_TARGETS; i++)
		{
			// check to see if the enemy we are attacking is alive first
			if (t_enemies[i].alive)
			{
				if (m_coordinates.x == t_enemies[i].coordinates.x)
				{
					if (m_coordinates.y == t_enemies[i].coordinates.y)
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
				if (m_coordinates.x == t_friendlies[i].coordinates.x)
				{
					if (m_coordinates.y == t_friendlies[i].coordinates.y)
					{
						std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
							<< t_friendlies[i].coordinates.y << std::endl;
						t_friendlies[i].alive = false;
					}
				}
			}
		}
	}

	if (m_payload == WarHead::NUCLEAR && m_armed)
	{
		if (m_coordinates.x == m_target.coordinates.x)
		{
			if (m_coordinates.y == m_target.coordinates.y)
			{
				std::cout << "Reached area. Dropping nuke..." << std::endl;
				for (int i = 0; i < t_MAX_TARGETS; i++)
				{
					if (t_enemies[i].alive)
					{
						// check the area we're attacking first
						if (t_enemies[i].coordinates.x == m_target.coordinates.x
							&& t_enemies[i].coordinates.y == m_target.coordinates.y)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}

						// then check surrounding areas
						if (t_enemies[i].coordinates.x == m_target.coordinates.x + 1
							|| t_enemies[i].coordinates.x == m_target.coordinates.x - 1)
						{
							std::cout << "Enemy hit at " << t_enemies[i].coordinates.x << ", "
								<< t_enemies[i].coordinates.y << std::endl;
							t_enemies[i].alive = false;
							continue;
						}

						if (t_enemies[i].coordinates.y == m_target.coordinates.y + 1
							|| t_enemies[i].coordinates.y == m_target.coordinates.y - 1)
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
						if (t_friendlies[i].coordinates.x == m_target.coordinates.x
							&& t_friendlies[i].coordinates.y == m_target.coordinates.y)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}

						// then check surrounding areas
						if (t_friendlies[i].coordinates.x == m_target.coordinates.x + 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.x == m_target.coordinates.x - 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}

						if (t_friendlies[i].coordinates.y == m_target.coordinates.y + 1)
						{
							std::cout << "Friendly hit at " << t_friendlies[i].coordinates.x << ", "
								<< t_friendlies[i].coordinates.y << std::endl;
							t_friendlies[i].alive = false;
							continue;
						}
						else if (t_friendlies[i].coordinates.y == m_target.coordinates.y - 1)
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
