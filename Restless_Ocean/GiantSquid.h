#pragma once

#include "NormalMonster.h"
#include "Player.h"

class GiantSquid : public NormalMonster
{
public:
	GiantSquid(const MonsterStat& stat) : NormalMonster(stat) {}

	void UseBasicAttack(Player* target) override {}
	void UseSpecialAttack(Player* target) override {}
	void TriggerPassive() override {}
};

