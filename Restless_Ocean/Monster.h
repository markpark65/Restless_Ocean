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
	AttributeType getMonsterType() const;
	bool isAlive() const;

	// 입력 받은 damage만큼 health 감소
	void takeDamage(int damage);

	//속도 감소
	void setSpeed(int newSpeed);

	// 몬스터 스탯 출력
	void showStat() const;

	// 몬스터 타입 string으로 변경
	std::string typeToString(AttributeType type) const;
};

