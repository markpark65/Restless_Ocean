#pragma once

#include <iostream>
#include <string>

//class Item;

struct MonsterStat
{
	std::string	name;
	int		health;
	int		attack;
};

struct MonsterReward
{
	int		exp;
	int		gold;
	//Item	item;
};

class Monster
{
protected:
	MonsterStat		monsterStat;
	MonsterReward	monsterReward;

public:
	virtual ~Monster() = default;

	virtual std::string getName() const = 0;
	virtual	int getHealth() const = 0;
	virtual	int getAttack() const = 0;
	virtual bool isAlive() const = 0;

	// 입력 받은 damage만큼 health 감소
	virtual void takeDamage(int damage) = 0;
};

