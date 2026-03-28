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

const std::string& Monster::getDescription() const
{
	return monsterStat.description;
}

Map Monster::getMap() const
{
	return monsterStat.map;
}

bool Monster::isAlive() const
{
    return monsterStat.health > 0;
}

//void Monster::takeDamage(int damage)
//{
//    if (damage < 0)
//    {
//        damage = 0;
//    }
//
//    monsterStat.health -= damage;
//
//    if (monsterStat.health <= 0)
//    {
//        monsterStat.health = 0;
//    }
//}

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

std::string Monster::mapToString(Map map) const
{
	switch (map)
	{
	case Map::BuildingMap:
		return "건물";
	case Map::SeaCaveMap:
		return "해저 동굴";
	case Map::CollapsedShipMap:
		return "침몰선";
	default:
		return "알 수 없음";
	}
}

void Monster::showStat() const
{
    cout << "\n===============================" << '\n';
    cout << "몬스터 이름: " << getName() << '\n';
	cout << "출현지  :" << mapToString(getMap()) << '\n';
	cout << "등급    :" << getRankName() << '\n';
    cout << "HP      :" << getHealth() << '\n';
    cout << "ATK     :" << getAttack() << '\n';
    cout << "SPEED   :" << getSpeed() << '\n';
	cout << "TYPE    :" << typeToString(getMonsterType()) << '\n';
	cout << "설명    :" << getDescription() << '\n';
    cout << "===============================" << '\n';
}
