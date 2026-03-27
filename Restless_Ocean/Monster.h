#pragma once

#include <iostream>
#include <string>
#include "DataType.h"

class Item;

struct MonsterStat
{
	std::string		name;
	int				health;
	int				attack;
	int				speed;
	AttributeType	type;
};

class Monster
{
protected:
	MonsterStat		monsterStat;

public:
	Monster(const MonsterStat& monsterStat);
	virtual ~Monster() = default;

	// Get Monster Stat
	const std::string& getName() const;
	int getHealth() const;
	int getAttack() const;
	int getSpeed()	const;
	bool isAlive() const;

	// 입력 받은 damage만큼 health 감소
	void takeDamage(int damage);

	// 몬스터 스탯 출력
	void showStat() const;
};

