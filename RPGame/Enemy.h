#pragma once
#include "Character.h"

class Enemy : public Character
{
	float m_drop_rate;

public:
	Enemy();
	Enemy(std::string name, int health, Weapon* weapon, Armor* armor, float drop_rate);
	Enemy(std::string name, Weapon* weapon, Armor* armor);

	~Enemy();

	//	Setter
	void SetDropRate(float const drop_rate) { m_drop_rate = drop_rate; };

	//	Getter
	float GetDropRate() const { return m_drop_rate; };

	//	Member functions
	Weapon* DropWeapon();
	void RandomName();
};