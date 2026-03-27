#pragma once
#include "BossMonster.h"
#include "Player.h"

class Leviathan : public BossMonster
{
public:
	Leviathan(const MonsterStat& stat) : BossMonster(stat) {}

	void useBasicAttack(Player* target) override {}
	void useSpecialAttack(Player* target) override {}
	void activatePassive() override {}
};
