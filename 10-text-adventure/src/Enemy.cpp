#include "../include/Enemy.h"

Enemy::Enemy(const std::string &enemyName, int hp) : name(enemyName), health(hp) {}

const std::string &Enemy::getName() const
{
    return name;
}

int Enemy::getHealth() const
{
    return health;
}

bool Enemy::isAlive() const
{
    return health > 0;
}

void Enemy::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;
}