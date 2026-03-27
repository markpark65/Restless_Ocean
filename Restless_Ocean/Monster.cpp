#include <iostream>

#include "Monster.h"
#include "Item.h"

using namespace std;

Monster::Monster(const MonsterStat& monsterStat)
    : monsterStat(monsterStat)
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

int Monster::getSpeed() const
{
    return monsterStat.speed;
}
void Monster::setSpeed(int newSpeed) {
	if (newSpeed < 10) {
		monsterStat.speed = 10;
	}
	else {
		monsterStat.speed = newSpeed;
	}
}

AttributeType Monster::getMonsterType() const
{
	return monsterStat.type;
}

bool Monster::isAlive() const
{
    return monsterStat.health > 0;
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

std::string Monster::typeToString(AttributeType type) const
{
	switch (type)
	{
	case AttributeType::Luminous:
		return "발광형";
	case AttributeType::Hidden:
		return "은닉형";
	case AttributeType::Giant:
		return "거대형";
	default:
		return "알 수 없음";
	}
}

void Monster::showStat() const
{
    cout << "===============================" << '\n';
    cout << "몬스터 이름: " << getName() << '\n';
    cout << "HP      :" << getHealth() << '\n';
    cout << "ATK     :" << getAttack() << '\n';
    cout << "SPEED   :" << getSpeed() << '\n';
	cout << "TYPE    :" << typeToString(getMonsterType()) << '\n';
    cout << "===============================" << '\n';
}
