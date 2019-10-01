#pragma once
#include "Enemy.h"
#include "Position.h"

struct Missle
{
	enum WarHead { EXPLOSIVE, NUCLEAR };

	WarHead m_payload;
	Coordinates m_coordinates;
	Target m_target;
	bool m_armed = false; // if the bombs can be used or not
	bool m_noRemainingWarheads = false; // are any warheads left
	int m_explosiveCode = 1234; // code for explosive warheads
	int m_nuclearCode = 2345; // code for nuclear warheads
	int m_userCode = 0; // code player put in
	int m_numberOfExplosives = 5; // how many explosives player can use
	int m_numberOfNuclears = 2; // how many nukes player can use

	void choosePayload();
	void inputCode();
	void arm();
	void choosePosition();
	void update(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
	void checkCollision(Target t_enemies[], Target t_friendlies[], int const t_MAX_TARGETS);
};

