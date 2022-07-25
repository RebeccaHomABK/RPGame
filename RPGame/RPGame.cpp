#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string.h>

#include "Weapon.h"
#include "Armor.h"
#include "Player.h"
#include "Enemy.h"

void PlayGame(Weapon* weapons, int choicesW, Armor* armors, int choicesA, std::string* adj, int choicesEA, std::string* enemies, int choicesEN);
bool Encounter(Player* player, Enemy* enemy);
void Round(Player* player, Enemy* enemy, int round);
void Rest(Player* player);

int main()
{
    //	Seed random
    srand((unsigned)time(NULL));

    //  Weapons
    Weapon unarmed = Weapon("None", 4, 7);
    Weapon sword = Weapon("Sword", 4, 6);
    Weapon axe = Weapon("Axe", 2, 8);
    Weapon bow = Weapon("Bow", 1, 5);
    Weapon weapons[4] = { unarmed, sword, axe, bow };

    //  Armor
    Armor none = Armor("None", 0, 0.0f);
    Armor light = Armor("Light", 10, 0.20f);
    Armor medium = Armor("Medium", 25, 0.10f);
    Armor heavy = Armor("Heavy", 50, 0.0f);
    Armor armors[4] = { none, light, medium, heavy };

    //  Enemies
    std::string adjectives[5] = {
        "", "Horrifying ", "Loathsome ", "Savage ", "Terrifying "
    };
    std::string enemies[5] = {
        "Ogre", "Chicken", "Slime", "Troll", "Goblin"
    };

    PlayGame(weapons, 4, armors, 4, adjectives, 5, enemies, 5);
}

//  Game setup
void PlayGame(Weapon* weapons, int choicesW, Armor* armors, int choicesA, std::string* adj, int choicesEA, std::string* enemies, int choicesEN)
{
    //  Set up the player character
    std::cout << "Welcome to the RPG!" << std::endl;
    
    //  Ask the player for their name
    std::cout << "Enter your name: ";
    std::string playerName;
    std::getline(std::cin, playerName);

    //  Get the player weapon
    int playerWeapon;
    do
    {
        system("cls");
        //  Display all weapons except for the "none" option
        std::cout << "WEAPONS AVAILABLE" << std::endl;
        for (int i = 1; i < choicesW; i++)
        {
            std::cout << i << ") " << weapons[i].GetItemName() << std::endl;
        }

        //  Get the player's weapon choice
        std::cout << "Choose your weapon: ";
        std::cin >> playerWeapon;

        if ((playerWeapon > 0) && (playerWeapon < choicesW))
        {
            break;
        }
    } while (true);

    //  Get the player's armor
    int playerArmor;
    do
    {
        system("cls");
        //  Display all armor except for the "none" option
        std::cout << "ARMOR AVAILABLE" << std::endl;
        for (int i = 1; i < choicesA; i++)
        {
            std::cout << i << ") " << armors[i].GetItemName() << std::endl;
        }

        std::cout << "Choose your armor: ";
        std::cin >> playerArmor;

        if ((playerArmor > 0) && (playerArmor < choicesA))
        {
            break;
        }
    } while (true);
    
    //  Show player character choices
    system("cls");
    std::cout << "You chose weapon #" << playerWeapon << " and armor #" << playerArmor << ".\n" << std::endl;
    Player* player = new Player(playerName, weapons[playerWeapon], armors[playerArmor]);
    player->GetStatus();

    //  Begin encounter(s)
    Enemy* enemy = new Enemy();

    bool quit = false;
    do
    {
        //  Get random weapon
        int random = rand() % choicesW;
        enemy->SetWeapon(weapons[random]);

        //  Get random armor
        random = rand() % choicesA;
        enemy->SetArmor(armors[random]);

        //  Get enemy's name
        random = rand() % choicesEA;
        std::string name = adj[random];
        random = rand() % choicesEN;
        name += enemies[random];
        enemy->SetName(name);

        std::cout << std::endl;

        //  Begin encounter
        quit = Encounter(player, enemy);
    } while (!quit);

    //  Cleans up player and enemy
    delete player;
    player = nullptr;

    delete enemy;
    enemy = nullptr;
}

bool Encounter(Player* player, Enemy* enemy)
{
    //  Encounter lasts until either the player or the enemy runs out of health
    int round = 1;
    do
    {
        Round(player, enemy, round);
        round++;
    } while ((player->GetHealth() > 0) && (enemy->GetHealth() > 0));

    //  Once the enemy is defeated, check if they dropped a weapon.
    if ((enemy->GetHealth() <= 0) && (player->GetHealth() > 0))
    {
        //  Tell player that they have defeated the enemy.
        std::cout << "You have defeated " << enemy->GetName() << "!\n" << std::endl;

        //  Check if enemy dropped weapon
        Weapon dropped = enemy->DropWeapon();
        if (dropped.GetItemName() != "None")
        {
            std::cout << enemy->GetName() << " dropped " << dropped.GetItemName() << " after being defeated.\n" << std::endl;
            player->SetInventory(dropped);
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

            if ((choice >= 1) && (choice <= 3))
            {
                if (choice == 2)
                {
                    Rest(player);
                }
                else if (choice == 3)
                {
                    std::cout << "You have completed your adventuring for tday. Goodbye!" << std::endl;
                    return true;
                }
                return false;
            }
            else
            {
                system("cls");
                std::cout << "Please make a valid choice." << std::endl;
            }
        } while (true);
    }
    else
    {
        std::cout << player->GetName() << " died fighting " << enemy->GetName() << std::endl;
        return true;
    }
}

void Round(Player* player, Enemy* enemy, int round)
{
    int healthEnemy = enemy->GetHealth();
    int healthPlayer = player->GetHealth();

    do
    {
        std::cout << player->GetName() << " VS " << enemy->GetName() << ": ROUND " << round << std::endl;
        
        //  Prompt user for a move
        std::cout << "1) Attack" << std::endl;

        std::cout << "Choose your move: ";
        int move;
        std::cin >> move;

        if (move == 1)
        {
            //  Player attacks enemy
            int attack = player->GetWeapon().GetDamage();
            healthEnemy -= attack;

            //  Enemy attacks player
            int counterattack = enemy->GetWeapon().GetDamage();
            healthPlayer -= counterattack;
            player->SetHealth(healthPlayer);

            //  Display how much health the player and enemy have
            enemy->SetHealth(healthEnemy);
            std::cout << "You attack " << enemy->GetName() << " with your " << player->GetWeapon().GetItemName() << ", causing " << attack << " damage." << std::endl;

            std::cout << enemy->GetName() << " attacks you, causing " << attack << " damage." << std::endl;

            std::cout << "You now have " << player->GetHealth() << " health left and " << enemy->GetName() << " has " << enemy->GetHealth() << " health left." << std::endl;
            break;
        }
        else
        {
            std::cout << "That is an invalid option." << std::endl;
        }
    } while (true);
}

void Rest(Player* player)
{
    //  Give the player 20 health for resting
    int healed = player->GetHealth() + 20;
    if (healed > 100)
    {
        healed = 100;
    }
    player->SetHealth(healed);

    //  Give player options to manage their inventory while resting
    bool resting = true;
    do
    {
        std::cout << "Rest Options" << std::endl;
        std::cout << "1) Check your inventory." << std::endl;
        std::cout << "2) Drop a weapon from your inventory." << std::endl;
        std::cout << "3) Equip a weapon from your inventory." << std::endl;
        std::cout << "4) Finish resting and move on to the next encounter." << std::endl;

        std::cout << "Pick an option: ";
        int rest;
        std::cin >> rest;

        switch (rest)
        {
        case 1:
        {
            player->GetInventory();
            break;
        }
        case 2:
        {
            player->DropWeapon();
            break;
        }
        case 3:
        {
            player->SwapWeapon();
            break;
        }
        case 4:
        {
            resting = false;
            std::cout << "You have finished resting and continue on to the next encounter." << std::endl;
            break;
        }
        default:
        {
            system("cls");
            std::cout << "That is not a valid option while resting. Try again." << std::endl;
        }
        }


    } while (resting);
}