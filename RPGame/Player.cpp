#include "Player.h"
#include <iostream>

//	Constructor
Player::Player()
	: Character("Player", Weapon(), Armor())
{
	for (int i = 0; i < 6; i++)
	{
		m_inventory[i] = Weapon();
	}
}

Player::Player(std::string name, int health, Weapon weapon, Armor armor)
	: Character(name, health, weapon, armor)
{
	for (int i = 0; i < 6; i++)
	{
		m_inventory[i] = Weapon();
	}
}

Player::Player(std::string name, Weapon weapon, Armor armor)
	: Character(name, weapon, armor)
{
	for (int i = 0; i < 6; i++)
	{
		m_inventory[i] = Weapon();
	}
}

//	Destructor
Player::~Player()
{

}

//	Member functions
void Player::SetInventory(Weapon weapon)
{
	bool isFull = true;
	
	//	Go through inventory to see if there's an available slot
	for (int i = 0; i < 6; i++)
	{
		if (m_inventory[i].GetItemName() == "None")
		{
			m_inventory[i] = weapon;
			isFull = false;
			break;
		}
	}

	//	If inventory is full, tell player what item they missed
	if (isFull)
	{
		std::cout << "Your inventory is full and you had to drop " << weapon.GetItemName() << "!" << std::endl;
	}
}

void Player::GetInventory()
{
	std::cout << "Current Inventory:" << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << i + 1 << ") " << m_inventory[i].GetItemName() << std::endl;
	}
}

void Player::DropWeapon()
{
	this->GetInventory();

	std::cout << "Pick a weapon to drop: ";
	int weapon;
	std::cin >> weapon;


}

void Player::SwapWeapon()
{
	int swap;
	Weapon temp;
	do {
		//	Display the weapons inventory
		this->GetInventory();

		//	Let the player choose a weapon to swap
		std::cout << "Choose a weapon to swap out: ";
		std::cin >> swap;

		if ((swap >= 1) && (swap <= 6))
		{
			//	Get the index of the weapon to be swapped
			swap--;

			//	Save data of the weapon in inventory
			temp = m_inventory[swap];
			//	Put the currently equipped weapon in inventory
			m_inventory[swap] = m_weapon;
			//	Equip the weapon that was in inventory
			m_weapon = temp;
			break;
		}
	} while (true);
	std::cout << "Your weapon is now " << m_weapon.GetItemName() << std::endl;
}