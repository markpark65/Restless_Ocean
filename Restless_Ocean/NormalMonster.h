#pragma once
#include "Monster.h"

class NormalMonster : public Monster
{
public:
	NormalMonster(const MonsterStat& stat) : Monster(stat) { rank = BossRank::Normal; }

	std::string getRankName() const override { return "일반 몬스터"; }

	void takeDamage(int damage) override
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
