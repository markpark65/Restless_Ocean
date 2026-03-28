#pragma once
#include "Monster.h"

class NormalMonster : public Monster
{
protected:
	std::string rewardArtifact;

public:
	NormalMonster(const MonsterStat& stat) : Monster(stat), rewardArtifact("None") {}

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
	const std::string& GetRewardArtifact() const override { return rewardArtifact; }
};
