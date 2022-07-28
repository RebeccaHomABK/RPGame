#pragma once
#include "Item.h"

class Weapon : public Item
{
	int m_damage_min;
	int m_damage_max;

public:
	Weapon();
	Weapon(std::string name, int damage_min, int damage_max);

	~Weapon();

	//	Setter
	void SetItemDamageMin(int const min) { m_damage_min = min; }
	void SetItemDamageMax(int const max) { m_damage_max = max; }

	//	Getter
	int GetItemDamageMin() const { return m_damage_min; }
	int GetItemDamageMax() const { return m_damage_max; }

	//	Member functions
	int GetDamage();
};