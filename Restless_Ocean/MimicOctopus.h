#pragma once
#include "BossMonster.h"
#include "Player.h"

class MimicOctopus : public BossMonster
{
public:
	MimicOctopus(const MonsterStat& stat) : BossMonster(stat) {}

	void UseBasicAttack(Player* target) override {}
	void UseSpecialAttack(Player* target) override {}
	void TriggerPassive() override {}
};

