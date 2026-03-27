#pragma once

#include "NormalMonster.h"
#include "Player.h"

class FootballFish : public NormalMonster
{
public:
	FootballFish(const MonsterStat& stat) : NormalMonster(stat) {}

	void useBasicAttack(Player* target) override {}
	void useSpecialAttack(Player* target) override {}
	void activatePassive() override {}
};

