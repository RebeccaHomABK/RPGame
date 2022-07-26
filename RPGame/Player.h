#pragma once

#include "Character.h"
#include <vector>

class Player : public Character
{
	std::vector<Item*> m_inventory;
	static unsigned int m_inventory_max;

public:
	Player();
	Player(std::string name, int health, Weapon* weapon, Armor* armor);
	Player(std::string name, Weapon* weapon, Armor* armor);

	~Player();

	//	Setter
	void SetInventory(Weapon* item);

	//	Getter
	void GetInventory();
	int GetInventorySize() const { return m_inventory.size(); }

	//	Member function
	void DropWeapon();
	void SwapWeapon();
	int GetWeapons(bool display);
};