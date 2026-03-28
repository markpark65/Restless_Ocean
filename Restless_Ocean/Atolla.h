#pragma once
#include "BossMonster.h"
#include "Player.h"

class Atolla : public BossMonster
{
public:
	Atolla(const MonsterStat& stat) : BossMonster(stat) {}

	void useBasicAttack(Player* target) override {}
	void useSpecialAttack(Player* target) override {}
	void activatePassive() override {}
};

