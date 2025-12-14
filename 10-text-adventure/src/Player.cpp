#include "../include/Player.h"

// constructor initializes player with full health and empty inventory
Player::Player(const std::string &playername) : name(playername), health(100), inventory{} {};

// take item method
void Player::takeItem(const std::string &item)
{
    inventory.push_back(item); // add item to back of inventory
}

// has item method
bool Player::hasItem(const std::string &item) const
{
    for (const std::string &i : inventory)
    {
        if (i == item)
        {
            return true;
        }
    }
    return false;
}