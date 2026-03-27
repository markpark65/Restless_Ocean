#pragma once
#include "Monster.h"
#include <string>

class BossMonster : public Monster
{
protected:
	std::string rewardArtifact;

public:
	BossMonster(const MonsterStat& stat) : Monster(stat), rewardArtifact(mapToString(stat.map)) {}

	const std::string& GetRewardArtifact() const { return rewardArtifact; }
	std::string getRankName() const override { return "보스 몬스터"; }
};

