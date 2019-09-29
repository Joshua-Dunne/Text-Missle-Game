#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Position.h"
#include "Missle.h"

/// <summary>
/// Joshua Dunne
/// C00241588
/// 28/09/19
/// </summary>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	void update(sf::Time t_deltaTime);

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	enum GameState{ MENU, GAMEPLAY, QUIT };

	GameState gameState{ MENU }; // start the game in the menu

	Missle playerDrone;
	int const static MAX_ENEMIES = 3;
	Target enemies[MAX_ENEMIES]{ {0,5}, {0,6}, {7,9} };
	Target friendlies[MAX_ENEMIES]{ {5,0},{6,0}, {7,0} };

};

#endif // !GAME_HPP

