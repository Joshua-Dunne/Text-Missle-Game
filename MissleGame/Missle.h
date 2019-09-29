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
	bool noRemainingWarheads = false;
	int explosiveCode = 1234;
	int nuclearCode = 2345;
	int userCode = 0;
	int numberOfExplosives = 1;
	int numberOfNuclears = 1;

	void choosePayload();
	void inputCode();
	void arm();
	void choosePosition();
	void update(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
	void checkCollision(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
};

