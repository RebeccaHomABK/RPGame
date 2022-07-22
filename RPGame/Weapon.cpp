#include "Weapon.h"
#include <stdlib.h>
#include <time.h>

//	Constructor
Weapon::Weapon()
	: Item("None")
	, m_damage_min(0)
	, m_damage_max(0)
{

}
Weapon::Weapon(std::string name, int damage_min, int damage_max)
	: Item(name)
	, m_damage_min(damage_min)
	, m_damage_max(damage_max)
{

}

//	Destructor
Weapon::~Weapon()
{

}

//	Member functions
int Weapon::GetDamage()
{
	//	Get the weapon damage
	int damage = m_damage_min;
	if (m_damage_min != m_damage_max)
	{
		//	Difference between minimum and maximum damage
		int difference = m_damage_max - m_damage_min;
		damage = m_damage_min + (rand() % (difference + 1));
	}
	return damage;
}