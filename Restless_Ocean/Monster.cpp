#include <iostream>

#include "Monster.h"

using namespace std;

Monster::Monster(const MonsterStat& monsterStat, const MonsterReward& monsterReward)
    : monsterStat(), monsterReward()
{
}


const std::string& Monster::getName() const
{
    return monsterStat.name;
}

int Monster::getHealth() const
{
    return monsterStat.health;
}

int Monster::getAttack() const
{
    return monsterStat.attack;
}

bool Monster::isAlive() const
{
    return monsterStat.health > 0;
}

int Monster::getExp() const
{
    return monsterReward.exp;
}

int Monster::getGold() const
{
    return monsterReward.gold;
}

void Monster::takeDamage(int damage)
{
    if (damage < 0)
    {
        damage = 0;
    }

    monsterStat.health -= damage;

    if (monsterStat.health <= 0)
    {
        monsterStat.health = 0;
    }
}

void Monster::showStat() const
{
    cout << "===============================" << '\n';
    cout << "몬스터 이름: " << getName() << '\n';
    cout << "HP      :" << getHealth() << '\n';
    cout << "ATK     :" << getAttack() << '\n';
    cout << "EXP     :" << getExp() << '\n';
    cout << "GOLD    :" << getGold() << " G" << '\n';
    cout << "===============================" << '\n';
}