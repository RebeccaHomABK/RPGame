#include "Player.h"
#include <iostream>

//	Constructor
Player::Player()
	: Character("Player", nullptr, nullptr)
{
	
}

Player::Player(std::string name, int health, Weapon* weapon, Armor* armor)
	: Character(name, health, weapon, armor)
{
	
}

Player::Player(std::string name, Weapon* weapon, Armor* armor)
	: Character(name, weapon, armor)
{
	
}

Player::~Player()
{
	//	Empty out the inventory
	while (!m_inventory.empty())
	{
		delete m_inventory.back();
		m_inventory.pop_back();
	}
}

//	Initialize static variables
unsigned int Player::m_inventory_max = 6;

//	Member functions
void Player::SetInventory(Weapon* weapon)
{
	if (m_inventory.size() < m_inventory_max)
	{
		//	If inventory is full, tell player what item they missed
		std::cout << "Your inventory is full and you had to drop " << weapon->GetItemName() << "!" << std::endl;
	}
	else
	{
		//	Add the item to the inventory
		m_inventory.push_back(weapon);
		std::cout << "You put " << weapon->GetItemName() << " into your inventory." << std::endl;
	}
	std::cout << std::endl;
}

void Player::GetInventory()
{
	std::cout << "INVENTORY" << std::endl;

	for (unsigned int i = 0; i < m_inventory.size(); i++)
	{
		std::cout << i + 1 << ") " << m_inventory[i]->GetItemName() << std::endl;
	}
	std::cout << std::endl;
}

void Player::DropWeapon()
{
	std::string dropped;
	do {
		//	Display the weapons inventory
		this->GetWeapons(true);

		//	Let the player choose a weapon to drop
		std::cout << "Pick a weapon to drop: ";
		unsigned int weapon;
		std::cin >> weapon;

		system("cls");

		if ((weapon >= 1) && (weapon <= m_inventory.size()))
		{
			unsigned int index = weapon - 1;
			dropped = m_inventory[index]->GetItemName();

			//	Drop the weapon
			m_inventory.erase(m_inventory.begin() + index);
			break;
		}
	} while (true);

	//	Tell player which weapon they dropped
	if (dropped != "")
	{
		std::cout << "Your dropped " << dropped << " from your inventory." << std::endl;
	}
	std::cout << std::endl;
}

void Player::SwapWeapon()
{
	unsigned int swap;

	do {
		//	Display the weapons inventory
		this->GetWeapons(true);

		//	Let the player choose a weapon to swap
		std::cout << "Choose a weapon to swap out: ";
		std::cin >> swap;

		if ((swap >= 1) && (swap <= m_inventory.size()))
		{
			//	Get the index of the weapon to be swapped
			swap--;

			//	Save data of the weapon in inventory
			Weapon* temp = dynamic_cast<Weapon*>(m_inventory[swap]);
			//	Put the currently equipped weapon in inventory
			m_inventory[swap] = dynamic_cast<Item*>(m_weapon);
			//	Equip the weapon that was in inventory
			m_weapon = temp;

			//	Clean up pointers
			temp = nullptr;
			break;
		}

		system("cls");
	} while (true);
	std::cout << "Your weapon is now " << m_weapon->GetItemName() << "." << std::endl;
	std::cout << std::endl;
}

int Player::GetWeapons(bool display)
{
	int count = 0;
	for (unsigned int i = 0; i < m_inventory.size(); i++)
	{
		//	Checks if an item is a weapon and counts/displays it 
		if (m_inventory[i]->GetItemType() == ItemType::Weapon)
		{
			if (display)
			{
				std::cout << i + 1 << ") " << m_inventory[i]->GetItemName() << std::endl;

			}
			count++;
		}
	}
	return count;
}