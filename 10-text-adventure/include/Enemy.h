#pragma once
#include <string>

class Enemy
{
private:
    std::string name;
    int health;

public:
    Enemy(const std::string &enemyName, int hp);
    const std::string &getName() const;
    int getHealth() const;
    bool isAlive() const;
    void takeDamage(int damage);
};