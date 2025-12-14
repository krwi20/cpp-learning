#include "../include/Game.h"

// constructor initializes room
Game::Game(const std::string &playerName) : player(playerName), currentRoomIndex(0)
{
    Room forest("You are in a dark forest.");
    forest.addExit("north");
    forest.addItem("rusty sword");

    Room cave("You are in a damp cave.");
    cave.addExit("south");
    cave.setEnemy("goblin", 50);

    rooms.push_back(forest);
    rooms.push_back(cave);
}

void Game::run()
{
    while (true)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "go north")
        {
            if (currentRoomIndex == 0)
            {
                currentRoomIndex = 1;
                std::cout << "You go north into the cave.\n";
            }
            else
            {
                std::cout << "You can't go that way.\n";
            }
        }
        else if (input == "go south")
        {
            if (currentRoomIndex == 1)
            {
                currentRoomIndex = 0;
                std::cout << "You go south into the forest.\n";
            }
            else
            {
                std::cout << "You can't go that way.\n";
            }
        }
        else if (input == "look")
        {
            std::cout << rooms[currentRoomIndex].getDescription() << "\n";
            const auto &items = rooms[currentRoomIndex].getItems();
            if (items.empty())
            {
                std::cout << "Items: none\n";
            }
            else
            {
                std::cout << "Items: ";
                for (size_t i = 0; i < items.size(); i++)
                {
                    if (i > 0)
                        std::cout << ", ";
                    std::cout << items[i];
                }
                std::cout << "\n";
            }
            const auto &exits = rooms[currentRoomIndex].getExits();
            std::cout << "Exits: ";
            for (size_t i = 0; i < exits.size(); i++)
            {
                if (i > 0)
                    std::cout << ", ";
                std::cout << exits[i];
            }
            std::cout << "\n";
        }
        else if (input == "quit")
        {
            break;
        }
        else if (input.substr(0, 5) == "take ")
        {
            std::string itemName = input.substr(5); // everything after "take "
            Room &current = rooms[currentRoomIndex];
            if (current.hasItem(itemName))
            {
                current.removeItem(itemName);
                player.takeItem(itemName);
                std::cout << "You take the " << itemName << ".\n";
            }
            else
            {
                std::cout << "There's no " << itemName << " here.\n";
            }
        }
        else if (input == "inventory")
        {
            const auto &inv = player.getInventory();
            if (inv.empty())
            {
                std::cout << "You are carrying nothing.\n";
            }
            else
            {
                std::cout << "Inventory: ";
                for (size_t i = 0; i < inv.size(); i++)
                {
                    if (i > 0)
                        std::cout << ", ";
                    std::cout << inv[i];
                }
                std::cout << "\n";
            }
        }
        else if (input.substr(0, 7) == "attack ")
        {
            std::string enemyName = input.substr(7);
            Room &current = rooms[currentRoomIndex];
            Enemy *enemy = current.getEnemy();

            if (enemy == nullptr)
            {
                std::cout << "There's no " << enemyName << " here to attack!\n";
            }
            else if (!enemy->isAlive())
            {
                std::cout << "The " << enemy->getName() << " is already dead.\n";
            }
            else
            {
                // Player attacks
                std::cout << "You attack the " << enemy->getName() << "!\n";
                enemy->takeDamage(25); // simple fixed damage

                if (!enemy->isAlive())
                {
                    std::cout << "You defeated the " << enemy->getName() << "!\n";
                    // Drop loot
                    current.addItem(enemy->getName() + " fang");
                }
                else
                {
                    // Enemy counterattacks
                    std::cout << "The " << enemy->getName() << " hits you back!\n";
                    // Optional: reduce player health (you can add this later)
                }
            }
        }
    }
}