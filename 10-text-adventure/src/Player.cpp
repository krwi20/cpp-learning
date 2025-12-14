#include "../include/Player.h"
#include <algorithm>

// constructor initializes player with full health and empty inventory
Player::Player(const std::string &playername) : name(playername), health(100), inventory{} {
    inventory.push_back("potion");
};

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

const std::vector<std::string> &Player::getInventory() const
{
    return inventory;
}

int Player::getHealth() const
{
    return health;
}

void Player::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;
}

void Player::heal(int amount)
{
    health += amount;
    if (health > 100)
        health = 100;
}

bool Player::removeItem(const std::string &item)
{
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end())
    {
        inventory.erase(it);
        return true;
    }
    return false;
}