#pragma once

#include "Character.h"

class Player : public Character
{
	Weapon m_inventory[6];

public:
	Player();
	Player(std::string name, int health, Weapon weapon, Armor armor);
	Player(std::string name, Weapon weapon, Armor armor);

	~Player();

	//	Setter
	void SetInventory(Weapon weapon);

	//	Getter
	void GetInventory();

	//	Member function
	void DropWeapon();
	void SwapWeapon();
};