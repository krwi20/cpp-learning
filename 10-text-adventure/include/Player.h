#pragma once
#include <iostream>
#include <vector>

class Player
{
private:
    std::string name;                   // player name
    int health;                         // player health
    std::vector<std::string> inventory; // inventory of item names

public:
    // Constructor
    Player(const std::string &playername);
    // Actions
    void takeItem(const std::string &item);
    bool hasItem(const std::string &item) const;
    const std::vector<std::string>& getInventory() const;
};