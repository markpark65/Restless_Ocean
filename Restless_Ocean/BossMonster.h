#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
	BossMonster(const MonsterStat& stat) : Monster(stat) {}

	std::string getRankName() const override { return "보스 몬스터"; }
};

