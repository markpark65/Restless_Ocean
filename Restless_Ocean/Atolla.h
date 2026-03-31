#pragma once
#include "BossMonster.h"
#include "Player.h"
#include "Random.h"
#include "GlobalVal.h"

class Atolla : public BossMonster
{
private:
	float poisionDamage = 0.1f;

public:
	Atolla(const MonsterStat& stat) : BossMonster(stat) { rewardArtifact = "해저 동굴 유적지"; }

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
		if (!target)
			return;

		g_sceneData.description += getName() + "가 촉수로 찌릅니다! \n ";

		g_sceneData.description += getName() + "는 추가로 " + target->getName() + "에게 독 데미지를 입힙니다! \n ";

		target->takeDamage(getAttack());

		cout << fixed;
		cout.precision(1);
		std::cout << getName() << "는 추가로 " << target->getName() << "에게 독 데미지를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * poisionDamage);
	}

	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		g_sceneData.description += getName() + "이 빛을 모아 폭발합니다! \n ";

		target->takeDamage(getAttack() * 2);
	}

	void activatePassive() override
	{
		poisionDamage += 0.2f;
		g_sceneData.description += getName() + "의 패시브가 발동됩니다! \n ";
		g_sceneData.description += getName() + "의 독 데미지가 0.1 증가하여 " + std::to_string(poisionDamage) + "가 됩니다! \n ";
	}
};

