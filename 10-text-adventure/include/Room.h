#pragma once
#include "Enemy.h"
#include <iostream>
#include <vector>

class Room
{
private:
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> exits;
    Enemy *enemy; // pointer to enemy

public:
    Room(const std::string &desc);
    void setEnemy(const std::string& name, int health);
    Enemy* getEnemy();
    void addItem(const std::string &item);
    bool hasItem(const std::string &item) const;
    bool removeItem(const std::string &item);
    void addExit(const std::string &direction);
    const std::string &getDescription() const;
    const std::vector<std::string> &getItems() const;
    const std::vector<std::string> &getExits() const;
};