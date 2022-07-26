#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string.h>

#include "Weapon.h"
#include "Player.h"
#include "Enemy.h"

void PlayGame();
bool Encounter(Player* player, Enemy* enemy);
void Round(Player* player, Enemy* enemy, int round);
void Rest(Player* player);

int main()
{
    //	Seed random
    srand((unsigned)time(NULL));

    PlayGame();
}

//  Game setup
void PlayGame()
{
    //  Set up player and enemy pointers
    Player* player = new Player();

    Enemy* enemy = new Enemy();
    enemy->SetDropRate(0.25f);

    //  Set up the player character
    std::cout << "Welcome to the RPG!" << std::endl;
    
    //  Ask the player for their name
    std::cout << "Enter your name: ";
    std::string playerName;
    std::getline(std::cin, playerName);
    player->SetName(playerName);

    //  Ask the player for their weapon
    int playerWeapon = player->ChooseWeapon(true);

    //  Ask the player for their armor
    int playerArmor = player->ChooseArmor(true);
    
    //  Show player character choices
    system("cls");
    std::cout << "You chose weapon #" << playerWeapon << " and armor #" << playerArmor << ".\n" << std::endl;
    player->GetStatus();
    std::cout << std::endl;

    //  Begin encounter(s)
    bool quit = false;
    do
    {
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
    //  Set up the enemy
    enemy->ChooseWeapon(false);
    enemy->ChooseArmor(false);
    enemy->RandomName();
    enemy->SetHealth(100);

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

            system("cls");
            if ((choice >= 1) && (choice <= 3))
            {
                if (choice == 2)
                {
                    Rest(player);
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
        std::cout << player->GetName() << " died fighting " << enemy->GetName() << "." << std::endl;
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

        system("cls");

        if (move == 1)
        {
            //  Player attacks enemy
            int playerAttack = enemy->TakeDamage(player);

            std::cout << "You attack " << enemy->GetName() << " with your " << player->GetWeapon().GetItemName();
            if (playerAttack == 0)
            {
                std::cout << " but the " << enemy->GetName() << " dodges your attack." << std::endl;
            }
            else
            {
                std::cout << ", causing " << playerAttack << " damage." << std::endl;
            }

            //  Enemy attacks player
            int opponentAttack = player->TakeDamage(enemy);

            std::cout << enemy->GetName() << " attacks you";
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

            std::cout << "You now have " << player->GetHealth() << " health left and " << enemy->GetName() << " has " << enemy->GetHealth() << " health left." << std::endl;

            std::cout << std::endl;
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
    bool emptyInventory = (player->GetInventorySize() == 0);
    do
    {
        std::cout << "REST OPTIONS" << std::endl;

        if (emptyInventory)
        {
            std::cout << "1) Finish resting and move on to the next encounter." << std::endl;
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

        if ((emptyInventory && (rest == 1)) ||(rest == 4))
        {
            std::cout << "You have finished resting and continue on to the next encounter." << std::endl;
            break;
        }
        else if (rest == 1)
        {
            player->GetInventory();
        }
        else if (rest == 2)
        {
            player->DropWeapon();
        }
        else if (rest == 3)
        {
            player->SwapWeapon();
        }
        else 
        {
            std::cout << "That is not a valid option while resting. Try again." << std::endl;
        }
    } while (true);
}