#include "../include/Game.h"

// constructor initializes room
Game::Game(const std::string &playerName) : player(playerName), currentRoomIndex(0)
{
    Room forest("You are in a dark forest.");
    forest.addExit("north");
    forest.addItem("rusty sword");
    forest.addItem("potion");

    Room cave("You are in a damp cave.");
    cave.addExit("south");
    cave.setEnemy("goblin", 50);

    Room castle("You stand before a fearsome dragon in a ruined castle!");
    castle.addExit("south");
    castle.setEnemy("dragon", 100); // strong dragon enemy

    rooms.push_back(forest);
    rooms.push_back(cave);
    rooms.push_back(castle);
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
            else if (currentRoomIndex = 1)
            {
                currentRoomIndex = 2;
                std::cout << "You go north into the castle.\n";
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
            else if (currentRoomIndex == 2)
            {
                currentRoomIndex = 1;
                std::cout << "You go south into the cave.\n";
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

                    // win condition
                    if (enemy->getName() == "dragon")
                    {
                        std::cout << "You slain the dragon and saved the kingdom!\n";
                        std::cout << "** YOU WIN! **\n";
                        break; // exit game loop
                    }
                }
                else
                {
                    // Enemy counterattacks
                    std::cout << "The " << enemy->getName() << " hits you for 20 damage!\n";
                    // reduce player health
                    player.takeDamage(20);

                    // check if player is dead
                    if (player.getHealth() <= 0)
                    {
                        std::cout << "You have been defeated! Game over.\n";
                        break; // exit game loop
                    }
                }
            }
        }
        else if (input == "status")
        {
            std::cout << "HP: " << player.getHealth() << "/100\n";
        }

        else if (input.substr(0, 4) == "use ")
        {
            std::string itemName = input.substr(4);
            if (player.hasItem(itemName))
            {
                if (itemName == "potion")
                {
                    player.heal(30);
                    // Remove potion from inventory
                    auto &inv = const_cast<std::vector<std::string> &>(player.getInventory());
                    // Better: add removeItem to Player (see note below)
                    std::cout << "You drink the potion and regain 30 HP!\n";
                }
                else
                {
                    std::cout << "You can't use that.\n";
                }
            }
            else
            {
                std::cout << "You don't have a " << itemName << ".\n";
            }
        }
    }
}