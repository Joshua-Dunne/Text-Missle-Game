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


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (gameState != GameState::QUIT)
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame); //60 fps
		}
	}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
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

			if (choice == 1)
			{
				gameState = GameState::QUIT;
			}
			else if (choice == 2)
			{
				gameState = GameState::GAMEPLAY;
			}
			else
			{
				std::cout << "Incorrect number given." << std::endl << std::endl;
			}
		}
	}

	while (gameState == GameState::GAMEPLAY)
	{
		playerDrone.choosePayload();

		// make sure that the warhead the player chose is still available
		if (!playerDrone.noRemainingWarheads)
		{
			playerDrone.choosePosition();
			playerDrone.inputCode();

			if (secretCheck())
			{
				break;
			}

			if (playerDrone.armed)
			{
				playerDrone.update(enemies, friendlies, MAX_ENEMIES);
			}
		}
		

		clearCheck();
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
	if (playerDrone.numberOfExplosives == 0
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
	}

	playerDrone.noRemainingWarheads = false; // reset so player can choose another warhead
}