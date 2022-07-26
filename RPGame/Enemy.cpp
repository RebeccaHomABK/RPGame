#include "Enemy.h"
#include <stdlib.h>

//	Constructor
Enemy::Enemy()
	: Character()
	, m_drop_rate(0.0f)
{

}

Enemy::Enemy(std::string name, int health, Weapon weapon, Armor armor, float drop_rate)
	: Character(name, health, weapon, armor)
	, m_drop_rate(drop_rate)
{

}

Enemy::Enemy(std::string name, Weapon weapon, Armor armor)
	: Character(name, weapon, armor)
	, m_drop_rate(0.25f)
{

}

Enemy::~Enemy()
{

}

//	Member functions
Weapon Enemy::DropWeapon()
{
	Weapon drop = Weapon();

	//	Gets the percentage
	float percent = (rand() % 100) / 100.0f;
	
	//	Drop item if percent is less than the drop rate
	if (percent < m_drop_rate)
	{
		drop = m_weapon;
	}
	return drop;
}


void Enemy::RandomName()
{
	//	Enemy name arrays
	constexpr int adjectiveSize = 7;
	constexpr int nameSize = 7;

	std::string adjectives[adjectiveSize] = {
			"", "Horrifying", "Loathsome", "Savage", "Terrifying", "Hungry", "Majestic"
	};
	std::string names[nameSize] = {
		"Ogre", "Chicken", "Slime", "Troll", "Goblin", "Duck", "Goose"
	};

	//	Sets a adjective
	int random = rand() % adjectiveSize;
	std::string name = adjectives[random];

	//	If there is an adjective put a space
	if (name != "")
	{
		name += " ";
	}

	//	Set up the random enemy name
	random = rand() % nameSize;
	name += names[random];
	this->SetName(name);
}