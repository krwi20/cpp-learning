#include "../include/Room.h"
#include <algorithm>

// constructor initializes room
Room::Room(const std::string &desc)
    : description(desc), enemy(nullptr) {}

void Room::setEnemy(const std::string &name, int health)
{
    enemy = new Enemy(name, health);
}

Enemy *Room::getEnemy() // We use a pointer because a room might not have an enemy (nullptr = no enemy).
{
    return enemy;
}

void Room::addItem(const std::string &item)
{
    items.push_back(item);
}

bool Room::removeItem(const std::string &item)
{
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end())
    {
        items.erase(it);
        return true;
    }
    return false;
}

bool Room::hasItem(const std::string &item) const
{
    for (const std::string &i : items)
    {
        if (i == item)
        {
            return true;
        }
    }
    return false;
}

void Room::addExit(const std::string &direction)
{
    exits.push_back(direction);
}

const std::string &Room::getDescription() const
{
    return description;
}

const std::vector<std::string> &Room::getItems() const
{
    return items;
}

const std::vector<std::string> &Room::getExits() const
{
    return exits;
}