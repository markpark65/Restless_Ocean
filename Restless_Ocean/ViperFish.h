#pragma once

#include "NormalMonster.h"
#include "Player.h"

class ViperFish : public NormalMonster
{
public:
	ViperFish(const MonsterStat& stat) : NormalMonster(stat) {}

	void UseBasicAttack(Player* target) override {}
	void UseSpecialAttack(Player* target) override {}
	void TriggerPassive() override {}
};

