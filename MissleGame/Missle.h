#pragma once
#include "Enemy.h"
#include "Position.h"

struct Missle
{
	enum WarHead { EXPLOSIVE, NUCLEAR };

	WarHead payload;
	Coordinates coordinates;
	Target target;
	bool armed = false; // if the bombs can be used or not
	bool noRemainingWarheads = false; // are any warheads left
	int explosiveCode = 1234; // code for explosive warheads
	int nuclearCode = 2345; // code for nuclear warheads
	int userCode = 0; // code player put in
	int numberOfExplosives = 5; // how many explosives player can use
	int numberOfNuclears = 2; // how many nukes player can use

	void choosePayload();
	void inputCode();
	void arm();
	void choosePosition();
	void update(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
	void checkCollision(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
};

