#pragma once
#include "Monster.h"
#include <string>

class Player;

class BossMonster : public Monster
{
public:
	BossMonster(const MonsterStat& stat) : Monster(stat) { rank = BossRank::Boss; }

	std::string getRankName() const override { return "보스 몬스터"; }

	virtual void showStat() const
	{
		std::cout << "\n===============================" << '\n';
		std::cout << "몬스터 이름: " << getName() << '\n';
		std::cout << "출현지  :" << mapToString(getMap()) << '\n';
		std::cout << "등급    :" << getRankName() << '\n';
		std::cout << "HP      :" << getHealth() << '\n';
		std::cout << "ATK     :" << getAttack() << '\n';
		std::cout << "SPEED   :" << getSpeed() << '\n';
		std::cout << "TYPE    :" << typeToString(getMonsterType()) << '\n';
		std::cout << "유물:   :" << getRewardArtifact() + " 유적" << '\n';
		std::cout << "설명    :" << getDescription() << '\n';
		std::cout << "===============================" << '\n';
	}

	virtual void takeDamage(int damage)
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
};

