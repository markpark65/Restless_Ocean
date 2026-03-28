#pragma once
#include "Monster.h"

class NormalMonster : public Monster
{
protected:
	std::string rewardArtifact;

public:
	NormalMonster(const MonsterStat& stat) : Monster(stat), rewardArtifact("None") {}

	std::string getRankName() const override { return "일반 몬스터"; }

	const std::string& GetRewardArtifact() const override { return rewardArtifact; }
};
