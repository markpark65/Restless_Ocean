#pragma once
#include "BossMonster.h"
#include "Player.h"

class MimicOctopus : public BossMonster
{
public:
	MimicOctopus(const MonsterStat& stat) : BossMonster(stat) {}

	void useBasicAttack(Player* target) override {}
	void useSpecialAttack(Player* target) override {}
	void activatePassive() override {}
};

