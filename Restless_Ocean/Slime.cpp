#include <random>

#include "Slime.h"

std::string Slime::getName() const
{
    return monsterStat.name;
}

int Slime::getHealth() const
{
    return monsterStat.health;
}

int Slime::getAttack() const
{
    return monsterStat.attack;
}

bool Slime::isAlive() const
{
    return monsterStat.health > 0;
}

void Slime::takeDamage(int damage)
{
    monsterStat.health -= damage;

    if (monsterStat.health <= 0)
    {
        monsterStat.health = 0;
    }
}
