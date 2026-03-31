#pragma once
#include <iostream>

#include "NormalMonster.h"
#include "Player.h"
#include "Random.h"
#include "GlobalVal.h"
#include "GameLogger.h"
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

		g_sceneData.description += getName() + "는 먹물을 발사합니다! \n ";
		GameLogger::getInstance().log(EventType::DamageTaken, target->getName(), getName(), getAttack());
		target->takeDamage(getAttack());
	}
	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		g_sceneData.description += getName() + "가 " + target->getName() + "에게 돌진합니다! \n ";

		int successAttack = Random::getRandomValue(0, 10);
		if (successAttack < 5)
		{
			int damage = getAttack() * 2;

			GameLogger::getInstance().log(EventType::DamageTaken, target->getName(), getName(), getAttack());
			target->takeDamage(damage);
		}
		else
		{
			g_sceneData.description += target->getName() + "는 " + getName() + "의 돌진을 피했습니다! \n ";
		}
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
		g_sceneData.description += getName() + "의 패시브가 발동됩니다! \n ";
		g_sceneData.description += getName() + "는 " + std::to_string(health) + "만큼 체력을 회복합니다! \n ";
		setHealth(getHealth() + health);
	}

	void setHealth(int health)
	{
		monsterStat.health = health;
	}
};

