#include "../include/Room.h"

// constructor initializes room
Room::Room(const std::string &desc) : description(desc), items{}, exits{} {}

void Room::addItem(const std::string &item)
{
    items.push_back(item);
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