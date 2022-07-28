#pragma once

#include "Player.h"
#include "Enemy.h"

class Game
{
	std::vector<Weapon*> m_weapons;
	std::vector<Armor*> m_armors;
	Player* m_player;
	Enemy* m_enemy;

public:
	Game();

	~Game();

	//	Member functions
	void PlayGame();
	bool Encounter();
	void Round(int round);
	void Rest();
};