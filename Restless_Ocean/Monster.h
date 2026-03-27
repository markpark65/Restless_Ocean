#pragma once

#include <iostream>
#include <string>
#include "DataType.h"

class Item;

enum class Map
{
	BuildingMap,
	SeaCaveMap,
	CollapsedShipMap,
};

struct MonsterStat
{
	std::string		name;
	int				health;
	int				attack;
	int				speed;
	AttributeType	type;
	std::string		description;
	Map				map;
};

class Player;
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
	const std::string& getDescription() const;
	Map getMap() const;

	// 입력 받은 damage만큼 health 감소
	void takeDamage(int damage);

	//속도 감소
	void setSpeed(int newSpeed);

	// 몬스터 스탯 출력
	void showStat() const;

	// 몬스터 타입 string으로 변경
	std::string typeToString(AttributeType type) const;
	std::string mapToString(Map map) const;

	virtual const std::string& GetRewardArtifact() const = 0;
	virtual std::string getRankName() const = 0;
	virtual void UseBasicAttack(Player* target)		= 0;
	virtual void UseSpecialAttack(Player* target)	= 0;
	virtual void TriggerPassive()					= 0;
};
