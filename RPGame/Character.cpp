#include "Character.h"
#include <iostream>

Character::Character()
	: m_name("Character")
	, m_health(0)
	, m_weapon(Weapon())
	, m_armor(Armor())
{

}

Character::Character(std::string name, int health, Weapon weapon, Armor armor)
	: m_name(name)
	, m_health(health)
	, m_weapon(weapon)
	, m_armor(armor)
{

}

Character::Character(std::string name, Weapon weapon, Armor armor)
	: m_name(name)
	, m_health(100)
	, m_weapon(weapon)
	, m_armor(armor)
{

}

Character::~Character()
{

}

//	Member functions
void Character::SetArmor(Armor armor)
{
	int updatedHealth = m_health - m_armor.GetHealthEx();
	updatedHealth += armor.GetHealthEx();
	m_health = updatedHealth;
	m_armor = armor;
}

void Character::GetStatus()
{
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Health: " << m_health << std::endl;
	std::cout << "Weapon: " << m_weapon.GetItemName() << std::endl;
	std::cout << "Armor: " << m_armor.GetItemName() << std::endl;
}