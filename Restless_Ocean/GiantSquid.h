#pragma once
#include <iostream>

#include "NormalMonster.h"
#include "Player.h"
#include "Random.h"

class GiantSquid : public NormalMonster
{
private:
	int maxHealth;

public:
	GiantSquid(const MonsterStat& stat) : NormalMonster(stat) { maxHealth = stat.health; }

	void useBasicAttack(Player* target) override
	{
		if (!target)
			return;

		std::cout << getName() << "가 일반 공격을 사용합니다!" << '\n';
		std::cout << getName() << "는 먹물을 발사합니다!" << '\n';
		target->takeDamage(getAttack());
	}
	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		std::cout << getName() << "가 특수 공격을 사용합니다!" << '\n';
		std::cout << getName() << "가 " << target->getName() << "에게 돌진합니다!" << '\n';
		target->takeDamage(getAttack() * 2);
	}

	void activatePassive() override
	{
		int health = 0;
		if (maxHealth - getHealth() > 20)
		{
			health = 20;
		}
		else
		{
			health = maxHealth - getHealth();
		}
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "는 " << health << "만큼 체력을 회복합니다!" << '\n';
		setHealth(getHealth() + health);
	}

	void setHealth(int health)
	{
		monsterStat.health = health;
	}
};

