#pragma once
#include "BossMonster.h"
#include "Player.h"

class Leviathan : public BossMonster
{
public:
	Leviathan(const MonsterStat& stat) : BossMonster(stat) {}

	void UseBasicAttack(Player* target) override {}
	void UseSpecialAttack(Player* target) override {}
	void TriggerPassive() override {}
};
