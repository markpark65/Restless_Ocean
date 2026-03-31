#pragma once

#include <iostream>
#include <string>
#include "DataType.h"

class Player;
class Item;

enum class BossRank
{
	None,
	Normal,
	Boss,
};

struct MonsterStat
{
	std::string		name = "";
	int				health = 0;
	int				attack = 0;
	int				speed = 0;
	AttributeType	type = AttributeType::Hidden;
	std::string		description = "";
	MapType			map = MapType::SeaCaveMap;

	std::string		asset = "";
};

class Player;
class Monster
{
protected:
	MonsterStat		monsterStat;
	BossRank		rank = BossRank::None;
	std::string		rewardArtifact;

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
	MapType getMap() const;
	BossRank getRank() const;
	const std::string& getRewardArtifact() const;
	const std::string& getAsset() const;

	// 입력 받은 damage만큼 health 감소
	virtual void takeDamage(int damage) = 0;

	//속도 감소
	void setSpeed(int newSpeed);

	// 몬스터 스탯 출력
	virtual void showStat() const;

	// 몬스터 타입 string으로 변경
	std::string typeToString(AttributeType type) const;
	std::string mapToString(MapType map) const;

	//virtual const std::string& GetRewardArtifact() const { return; };
	virtual std::string getRankName() const = 0;
	virtual void useBasicAttack(Player* target) = 0;
	virtual void useSpecialAttack(Player* target) = 0;
	virtual void activatePassive() = 0;
};
