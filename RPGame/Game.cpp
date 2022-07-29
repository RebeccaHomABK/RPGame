#include "Game.h"

#include <iostream>

//	Constructor
Game::Game()
{
	//	Set up the weapon choices
	m_weapons.push_back(new Weapon("None", 4, 7));
	m_weapons.push_back(new Weapon("Sword", 4, 6));
	m_weapons.push_back(new Weapon("Axe", 2, 8));
	m_weapons.push_back(new Weapon("Bow", 1, 5));

	//	Set up the armor choices
	m_armors.push_back(new Armor("None", 0, 0.0f));
	m_armors.push_back(new Armor("Light", 10, 0.20f));
	m_armors.push_back(new Armor("Medium", 25, 0.10f));
	m_armors.push_back(new Armor("Heavy", 50, 0.0f));

	//	Create the player and enemy
	m_player = new Player();
	m_enemy = new Enemy();
}

//	Destructor
Game::~Game()
{
	//	Empty out weapons
	while (!m_weapons.empty())
	{
		delete m_weapons.back();
		m_weapons.pop_back();
	}

	//	Empty out armor sets
	while (!m_armors.empty())
	{
		delete m_armors.back();
		m_armors.pop_back();
	}

	//	Delete player
	delete m_player;
	m_player = nullptr;

	//	Delete enemy
	delete m_enemy;
	m_enemy = nullptr;
}

//	Member functions
void Game::PlayGame()
{
	//	Set up the player character
	std::cout << "Welcome to the RPG!" << std::endl;

	//  Ask the player for their name
	std::cout << "Enter your name: ";
	std::string playerName;
	std::getline(std::cin, playerName);
	m_player->SetName(playerName);

	//  Ask the player for their weapon
	int playerWeapon = m_player->ChooseWeapon(true, m_weapons);

	//  Ask the player for their armor
	int playerArmor = m_player->ChooseArmor(true, m_armors);

	//  Show player character choices
	system("cls");
	std::cout << "You chose weapon #" << playerWeapon << " and armor #" << playerArmor << ".\n" << std::endl;
	m_player->GetStatus();
	std::cout << std::endl;

	//  Begin encounter(s) until player quits or dies
	do
	{
		if (this->Encounter())
		{
			break;
		}
	} while (true);
}


bool Game::Encounter()
{
    //  Set up the enemy
    m_enemy->ChooseWeapon(false, m_weapons);
    m_enemy->ChooseArmor(false, m_armors);
    m_enemy->RandomName();
    m_enemy->SetHealth(100);

    //  Encounter lasts until either the player or the enemy runs out of health
    int round = 1;
    do
    {
        Round(round);
        round++;
    } while ((m_player->GetHealth() > 0) && (m_enemy->GetHealth() > 0));

    //  Once the enemy is defeated, check if they dropped a weapon.
    if ((m_enemy->GetHealth() <= 0) && (m_player->GetHealth() > 0))
    {
        //  Tell player that they have defeated the enemy.
        std::cout << "You have defeated " << m_enemy->GetName() << "!\n" << std::endl;

        //  Check if enemy dropped weapon
        Weapon* dropped = m_enemy->DropWeapon();
        if ((dropped != nullptr) && (dropped->GetItemName() != "None"))
        {
            std::cout << m_enemy->GetName() << " dropped " << dropped->GetItemName() << " after being defeated.\n" << std::endl;
            m_player->SetInventory(dropped);
        }

        //  Allow player to continue, rest, or quit
        do
        {
            std::cout << "What would you like to do?" << std::endl;
            std::cout << "1) On to the next encounter!" << std::endl;
            std::cout << "2) Rest before the next encounter." << std::endl;
            std::cout << "3) Retire from adventuring. (Quit)" << std::endl;
            std::cout << "------" << std::endl;
            std::cout << "Pick your next move: ";
            int choice;
            std::cin >> choice;

            system("cls");
            if ((choice >= 1) && (choice <= 3))
            {
                if (choice == 2)
                {
                    Rest();
                }
                else if (choice == 3)
                {
                    std::cout << "You have completed your adventuring for today. Goodbye!" << std::endl;
                    return true;
                }

                std::cout << std::endl;
                return false;
            }
            else
            {
                std::cout << "Please make a valid choice." << std::endl;
            }
        } while (true);
    }
    else
    {
        std::cout << m_player->GetName() << " died fighting " << m_enemy->GetName() << "." << std::endl;
        return true;
    }
}

void Game::Round(int round)
{
    do
    {
        std::cout << m_player->GetName() << " VS " << m_enemy->GetName() << ": ROUND " << round << std::endl;

        //  Prompt user for a move
        std::cout << "1) Attack" << std::endl;

        std::cout << "Choose your move: ";
        int move;
        std::cin >> move;

        system("cls");

        if (move == 1)
        {
            //  Player attacks enemy
            int playerAttack = m_enemy->TakeDamage(m_player);

            std::cout << "You attack " << m_enemy->GetName() << " with your " << m_player->GetWeapon()->GetItemName();
            if (playerAttack == 0)
            {
                std::cout << " but the " << m_enemy->GetName() << " dodges your attack." << std::endl;
            }
            else
            {
                std::cout << ", causing " << playerAttack << " damage." << std::endl;
            }

            //  Enemy attacks player
            int opponentAttack = m_player->TakeDamage(m_enemy);

            std::cout << m_enemy->GetName() << " attacks you";
            if (opponentAttack == 0)
            {
                std::cout << " but you dodge the attack." << std::endl;
            }
            else
            {
                std::cout << ", causing " << opponentAttack << " damage." << std::endl;
            }

            //  Display how much health the player and enemy have
            std::cout << std::endl;

            std::cout << m_player->GetName() << ": " << m_player->GetHealth() << "     " << m_enemy->GetName() << ": " << m_enemy->GetHealth() << std::endl;

            std::cout << std::endl;
            break;
        }
        else
        {
            std::cout << "That is an invalid option." << std::endl;
        }
    } while (true);
}

void Game::Rest()
{
    //  Give the player 20 health for resting
    int healed = m_player->GetHealth() + 20;
    if (healed > 100)
    {
        healed = 100;
    }
    m_player->SetHealth(healed);

    //  Give player options to manage their inventory while resting
    do
    {
        std::cout << "REST OPTIONS" << std::endl;

        if (m_player->GetInventorySize() == 0)
        {
            std::cout << "1) Finish resting and move on to the next encounter." << std::endl;
        }
        else if (m_player->GetWeapons(false) == 0)
        {
            std::cout << "1) Check your inventory." << std::endl;
            std::cout << "2) Finish resting and move on to the next encounter." << std::endl;
        }
        else
        {
            std::cout << "1) Check your inventory." << std::endl;
            std::cout << "2) Drop a weapon from your inventory." << std::endl;
            std::cout << "3) Equip a weapon from your inventory." << std::endl;
            std::cout << "4) Finish resting and move on to the next encounter." << std::endl;
        }


        std::cout << "Pick an option: ";
        int rest;
        std::cin >> rest;

        system("cls");

        if (((m_player->GetInventorySize() == 0) && (rest == 1))
            || ((m_player->GetWeapons(false) == 0) && (rest == 2)) 
            || (rest == 4))
        {
            std::cout << "You have finished resting and continue on to the next encounter." << std::endl;
            break;
        }
        else if (rest == 1)
        {
            m_player->GetInventory();
        }
        else if (rest == 2)
        {
            m_player->DropWeapon();
        }
        else if (rest == 3)
        {
            m_player->SwapWeapon();
        }
        else
        {
            std::cout << "That is not a valid option while resting. Try again." << std::endl;
        }
    } while (true);
}