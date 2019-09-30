/// <summary>
/// Joshua Dunne
/// c00241588
/// 28/09/19
/// </summary>

#include "Game.h"
#include <iostream>

Game::Game()
{
	m_exitGame = false;
}
Game::~Game()
{
}


/// </summary>
void Game::run()
{	
	while (gameState != GameState::QUIT)
	{
		update(); // while we're playing the game (not done with it) update everything
	}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update()
{
	while (gameState == GameState::MENU)
	{
		int choice = 0;

		while (choice != 1 && choice != 2)
		{
			std::cout << "Welcome to Missle Game." << std::endl;
			std::cout << "Enter 2 to play, 1 To quit: ";
			std::cin >> choice;
			std::cout << std::endl;

			if (choice == 1) // if they don't want to play, end the game
			{
				gameState = GameState::QUIT;
			}
			else if (choice == 2) // if they want to play, go into the game
			{
				gameState = GameState::GAMEPLAY;
			}
			else // if they put anything else in, reloop
			{
				std::cout << "Incorrect number given." << std::endl << std::endl;
			}
		}
	}

	while (gameState == GameState::GAMEPLAY)
	{
		playerDrone.choosePayload(); // get the player to choose a warhead

		// make sure that the warhead the player chose is still available
		if (!playerDrone.noRemainingWarheads)
		{
			playerDrone.choosePosition(); // get the player to choose a target

			if (secretCheck())
			{
				break; // if the player blows themselves up...
			}

			if (playerDrone.armed) // if the drone is ready to fire
			{
				playerDrone.update(enemies, friendlies, MAX_ENEMIES); // fire away
			} // otherwise just go back around the loop
		}
		

		clearCheck(); // see if the player has won/lost
	}
}

/// <summary>
/// See if the player had a great idea to blow themselves up.
/// </summary>
/// <returns>If the player has lost through blowing themselves up.</returns>
bool Game::secretCheck()
{
	bool hasLost = false;

	if (playerDrone.target.coordinates.x == 0 &&
		playerDrone.target.coordinates.y == 0 && playerDrone.armed)
	{
		std::cout << "You blew yourself up... GAME OVER.";
		gameState = GameState::QUIT;
		hasLost = true;
	}

	return hasLost;
}

/// <summary>
/// See if the player has won or lost yet
/// </summary>
void Game::clearCheck()
{
	int enemyAliveCheck = 0;
	int friendlyAliveCheck = 0;

	for (int i = 0; i < MAX_ENEMIES; i++)
	{

		if (!enemies[i].alive)
		{
			enemyAliveCheck++;
		}

		if (!friendlies[i].alive)
		{
			friendlyAliveCheck++;
		}
	}

	// if the player runs out of warheads, they lose
	
	// let the player win even if they killed all friendlies and enemies in the same run
	if (enemyAliveCheck == MAX_ENEMIES && friendlyAliveCheck == MAX_ENEMIES)
	{
		std::cout << "All enemies and friendlies are killed." << std::endl;
		std::cout << "Casualties are expected in this line of work. Good job.";
		gameState = GameState::QUIT;
	}
	else if (enemyAliveCheck == MAX_ENEMIES)
	{ // otherwise if all enemies are killed, let them win
		std::cout << "All enemies defeated. Good work." << std::endl;
		gameState = GameState::QUIT;
	}
	else if (friendlyAliveCheck == MAX_ENEMIES)
	{ // finally if all friendlies are killed, but not all enemies, they lose.
		std::cout << "All friendlies dead. You're the last one left..." << std::endl;
		gameState = GameState::QUIT;
	} else if (playerDrone.numberOfExplosives == 0
		&& playerDrone.numberOfNuclears == 0)
	{
		int aliveEnemies = 0;
		int aliveFriendlies = 0;

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			// check to see if the enemy we are attacking is alive first
			if (enemies[i].alive)
			{
				aliveEnemies++;
			}

			if (friendlies[i].alive)
			{
				aliveFriendlies++;
			}
		}

		std::cout << "You are out of Warheads." << std::endl;
		std::cout << "You didn't complete your mission..." << std::endl;
		std::cout << "Remaining Enemies: " << aliveEnemies << std::endl;
		std::cout << "Remaining Friendlies: " << aliveFriendlies << std::endl << std::endl;
		gameState = GameState::QUIT;
	}

	playerDrone.noRemainingWarheads = false; // reset so player can choose another warhead
}