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
		playerDrone.choosePosition();
		playerDrone.inputCode();

		if (playerDrone.armed)
		{
			playerDrone.update(enemies, MAX_ENEMIES);
		}

		int aliveCheck = 0;

		for (int i = 0; i < MAX_ENEMIES; i++)
		{

			if (!enemies[i].alive)
			{
				aliveCheck++;
			}
		}

		if (aliveCheck == MAX_ENEMIES)
		{
			std::cout << "All enemies defeated. Good work." << std::endl;
			gameState = GameState::QUIT;
		}
	}
}