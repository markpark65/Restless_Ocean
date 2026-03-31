#pragma once

#include "NormalMonster.h"
#include "Player.h"
#include "GlobalVal.h"

class FootballFish : public NormalMonster
{
private:
	bool readyExplode = false;

public:
	FootballFish(const MonsterStat& stat) : NormalMonster(stat) {}

	void useBasicAttack(Player* target) override
	{
		if (!target)
			return;

		if (readyExplode)
		{
			int damage = getAttack() + 30;
			g_sceneData.description += getName() + "가 축적한 빛을 폭발시킵니다! \n ";
			target->takeDamage(damage);
		}
		else
		{
			g_sceneData.description += getName() + "이 몸통 박치기를 사용합니다! \n ";

			target->takeDamage(getAttack());
		}
	}
	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		g_sceneData.description += getName() + "가 빛을 모아 폭발을 준비합니다! \n ";
	
		readyExplode = true;
	}

	void activatePassive() override
	{
		int enhancedAttack = 10;
		g_sceneData.description += getName() + "의 패시브가 발동됩니다! \n ";
		g_sceneData.description += getName() + "의 공격력이 " + std::to_string(enhancedAttack)+"만큼 증가합니다 \n ";

		setAttack(getAttack() + enhancedAttack);
	}

	void setAttack(int attack)
	{
		monsterStat.attack = attack;
	}
};

