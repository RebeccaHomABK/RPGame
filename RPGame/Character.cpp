#include "Character.h"
#include <iostream>

Character::Character()
	: m_name("Character")
	, m_health(100)
	, m_weapon(nullptr)
	, m_armor(nullptr)
{

}

Character::Character(std::string name, int health, Weapon* weapon, Armor* armor)
	: m_name(name)
	, m_health(health)
	, m_weapon(weapon)
{
	m_armor = armor;
	if (m_armor != nullptr)
	{
		m_health += m_armor->GetHealthEx();
	}
}

Character::Character(std::string name, Weapon* weapon, Armor* armor)
	: m_name(name)
	, m_health(100)
	, m_weapon(weapon)
{
	m_armor = armor;
	if (m_armor != nullptr)
	{
		m_health += m_armor->GetHealthEx();
	}
}

Character::~Character()
{
	//	Remove weapon and armor
	m_weapon = nullptr;
	m_armor = nullptr;
}

//	Member functions
void Character::SetArmor(Armor* armor)
{
	int updatedHealth = m_health - 
		((m_armor != nullptr) ? m_armor->GetHealthEx() : 0);
	updatedHealth += armor->GetHealthEx();
	m_health = updatedHealth;
	m_armor = armor;
}

void Character::GetStatus()
{
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Health: " << m_health << std::endl;
	std::cout << "Weapon: " << m_weapon->GetItemName() << std::endl;
	std::cout << "Armor: " << m_armor->GetItemName() << std::endl;
}

int Character::ChooseWeapon(bool choice, std::vector <Weapon*>& weapons)
{
	unsigned int weapon;
	if (choice)
	{
		//	Let player choose a weapon
		do
		{
			system("cls");
			//  Display all weapons except for the "none" option
			std::cout << "WEAPONS AVAILABLE" << std::endl;
			for (unsigned int i = 1; i < weapons.size(); i++)
			{
				std::cout << i << ") " << weapons[i]->GetItemName() << std::endl;
			}

			//  Get the player's weapon choice
			std::cout << "Choose your weapon: ";
			std::cin >> weapon;

			if ((weapon > 0) && (weapon < weapons.size()))
			{
				break;
			}
		} while (true);
	}
	else
	{
		//	Randomly select a weapon
		weapon = rand() % weapons.size();
	}

	//	Set the weapon
	this->SetWeapon(weapons[weapon]);
	return weapon;
}

int Character::ChooseArmor(bool choice, std::vector<Armor*>& armors)
{
	unsigned int armor;
	if (choice)
	{
		//  Get the player's armor
		do
		{
			system("cls");
			//  Display all armor except for the "none" option
			std::cout << "ARMOR AVAILABLE" << std::endl;
			for (unsigned int i = 1; i < armors.size(); i++)
			{
				std::cout << i << ") " << armors[i]->GetItemName() << std::endl;
			}

			std::cout << "Choose your armor: ";
			std::cin >> armor;

			if ((armor > 0) && (armor < armors.size()))
			{
				break;
			}
		} while (true);
	}
	else
	{
		//	Randomly select armor
		armor = rand() % armors.size();
	}

	this->SetArmor(armors[armor]);
	return armor;
}

int Character::TakeDamage(Character* opponent)
{
	//	Gets the opponents attack from a weapon
	int attack = opponent->GetWeapon()->GetDamage();
	float dodge = (rand() % 100) / 100.0f;
	
	//	If the character dodges, then they take 0 points in damage
	if (dodge < m_armor->GetDodgeRate())
	{
		attack = 0;
	}

	//	Reduce the damage taken from health
	m_health -= attack;
	return attack;
}