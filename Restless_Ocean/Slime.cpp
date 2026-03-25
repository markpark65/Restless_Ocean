#include <random>

#include "Slime.h"

Slime::Slime(int level)
    : Monster("슬라임", 0, 0)
{
    // 재사용 가능한 난수 엔진(static)
    static std::mt19937 gen(std::random_device{}());
    // 레벨에 따른 체력, 공격력 범위를 설정하기 위한 난수열
    std::uniform_int_distribution<int> healthDis(20, 30);
    std::uniform_int_distribution<int> attackDis(5, 10);

    health = healthDis(gen) * level;
    attack = attackDis(gen) * level;
}

std::string Slime::getName() const
{
    return name;
}

int Slime::getHealth() const
{
    return health;
}

int Slime::getAttack() const
{
    return attack;
}

bool Slime::isAlive() const
{
    return health > 0;
}

void Slime::takeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        health = 0;
    }
}
