#include "../include/Game.h"

// constructor initializes room
Game::Game(const std::string &playerName) : player(playerName), currentRoomIndex(0)
{
    Room forest("You are in a dark forest.");
    forest.addExit("north");
    forest.addItem("rusty sword");

    Room cave("You are in a damp cave.");
    cave.addExit("south");

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
    }
}