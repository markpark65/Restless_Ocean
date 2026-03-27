#pragma once
#include "BossMonster.h"
#include "Player.h"

class Atolla : public BossMonster
{
public:
	Atolla(const MonsterStat& stat) : BossMonster(stat) {}

	void UseBasicAttack(Player* target) override {}
	void UseSpecialAttack(Player* target) override {}
	void TriggerPassive() override {}
};

