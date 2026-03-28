#pragma once
#include "BossMonster.h"
#include "Player.h"

class MimicOctopus : public BossMonster
{
public:
	MimicOctopus(const MonsterStat& stat) : BossMonster(stat) {}

	void takeDamage(int damage) override
	{
		if (damage < 0)
		{
			damage = 0;
		}

		monsterStat.health -= damage;

		if (monsterStat.health <= 0)
		{
			monsterStat.health = 0;
		}
	}

	void useBasicAttack(Player* target) override
	{
	}

	void useSpecialAttack(Player* target) override
	{

	}

	void activatePassive() override
	{

	}
};

