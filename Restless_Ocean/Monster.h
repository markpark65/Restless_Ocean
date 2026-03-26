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

struct MonsterReward
{
	int		exp = 50;
	int		gold = 50;
	Item*	item;
};

class Monster
{
protected:
	MonsterStat		monsterStat;
	MonsterReward	monsterReward;

public:
	Monster(const MonsterStat& monsterStat, const MonsterReward& monsterReward);
	virtual ~Monster() = default;

	// Get Monster Stat
	const std::string& getName() const;
	int getHealth() const;
	int getAttack() const;
	int getSpeed()	const;
	bool isAlive() const;

	// Get Monster Reward
	int getExp() const;
	int getGold() const;
	Item* getItem() const;

	// 입력 받은 damage만큼 health 감소
	void takeDamage(int damage);

	// 몬스터 스탯 출력
	void showStat() const;
};

