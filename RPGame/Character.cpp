#include "Character.h"
#include <iostream>

Character::Character()
	: m_name("Character")
	, m_health(0)
	, m_weapon(Weapon())
	, m_armor(Armor())
{
	m_armor = Armor();
	m_health += m_armor.GetHealthEx();
}

Character::Character(std::string name, int health, Weapon weapon, Armor armor)
	: m_name(name)
	, m_health(health)
	, m_weapon(weapon)
{
	m_armor = armor;
	m_health += m_armor.GetHealthEx();
}

Character::Character(std::string name, Weapon weapon, Armor armor)
	: m_name(name)
	, m_health(100)
	, m_weapon(weapon)
{
	m_armor = armor;
	m_health += m_armor.GetHealthEx();
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

int Character::ChooseWeapon(bool choice)
{
	constexpr int weaponSize = 4;

	Weapon unarmed = Weapon("None", 4, 7);
	Weapon sword = Weapon("Sword", 4, 6);
	Weapon axe = Weapon("Axe", 2, 8);
	Weapon bow = Weapon("Bow", 1, 5);
	Weapon weapons[weaponSize] = { unarmed, sword, axe, bow };

	int weapon;
	if (choice)
	{
		//	Let player choose a weapon
		do
		{
			system("cls");
			//  Display all weapons except for the "none" option
			std::cout << "WEAPONS AVAILABLE" << std::endl;
			for (int i = 1; i < weaponSize; i++)
			{
				std::cout << i << ") " << weapons[i].GetItemName() << std::endl;
			}

			//  Get the player's weapon choice
			std::cout << "Choose your weapon: ";
			std::cin >> weapon;

			if ((weapon > 0) && (weapon < weaponSize))
			{
				break;
			}
		} while (true);
	}
	else
	{
		//	Randomly select a weapon
		weapon = rand() % weaponSize;
	}

	//	Set the weapon
	this->SetWeapon(weapons[weapon]);
	return weapon;
}

int Character::ChooseArmor(bool choice)
{
	constexpr int armorSize = 4;

	Armor none = Armor("None", 0, 0.0f);
	Armor light = Armor("Light", 10, 0.20f);
	Armor medium = Armor("Medium", 25, 0.10f);
	Armor heavy = Armor("Heavy", 50, 0.0f);
	Armor armors[armorSize] = { none, light, medium, heavy };

	int armor;
	if (choice)
	{
		//  Get the player's armor
		do
		{
			system("cls");
			//  Display all armor except for the "none" option
			std::cout << "ARMOR AVAILABLE" << std::endl;
			for (int i = 1; i < armorSize; i++)
			{
				std::cout << i << ") " << armors[i].GetItemName() << std::endl;
			}

			std::cout << "Choose your armor: ";
			std::cin >> armor;

			if ((armor > 0) && (armor < armorSize))
			{
				break;
			}
		} while (true);
	}
	else
	{
		//	Randomly select armor
		armor = rand() % armorSize;
	}

	this->SetArmor(armors[armor]);
	return armor;
}

int Character::TakeDamage(Character* opponent)
{
	//	Gets the opponents attack from a weapon
	int attack = opponent->GetWeapon().GetDamage();
	float dodge = (rand() % 100) / 100.0f;
	
	//	If the character dodges, then they take 0 points in damage
	if (dodge < m_armor.GetDodgeRate())
	{
		attack = 0;
	}

	//	Reduce the damage taken from health
	m_health -= attack;
	return attack;
}