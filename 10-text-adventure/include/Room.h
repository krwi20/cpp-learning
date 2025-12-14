#pragma once
#include <iostream>
#include <vector>

class Room
{
private:
    std::string description;
    std::vector<std::string> items;
    std::vector<std::string> exits;

public:
    Room(const std::string &desc);
    void addItem(const std::string &item);
    bool hasItem(const std::string &item) const;
    void addExit(const std::string &direction);
    const std::string &getDescription() const;
    const std::vector<std::string> &getItems() const;
    const std::vector<std::string> &getExits() const;
};