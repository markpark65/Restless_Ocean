#pragma once
#include "BossMonster.h"
#include "Player.h"
#include "Random.h"
#include "GlobalVal.h"

class MimicOctopus : public BossMonster
{
private:
	bool isMimic = false;

public:
	MimicOctopus(const MonsterStat& stat) : BossMonster(stat) { rewardArtifact = "무너진 건물 유적지"; }

	void takeDamage(int damage) override
	{
		if (isMimic)
		{
			g_sceneData.description += getName() + "이 아닌 다른 대상을 공격했습니다! \n ";
			//std::cout << getName() << "이 아닌 다른 대상을 공격했습니다!" << '\n';
			isMimic = false;
			return;
		}

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

		//g_sceneData.description += getName() + "가 일반 공격을 사용했습니다! \n ";
		g_sceneData.description += getName() + "가 먹물을 발사합니다! \n ";
		//std::cout << getName() << "가 일반 공격을 사용했습니다!" << '\n';
		//std::cout << getName() << "가 먹물을 발사합니다!" << '\n';
		GameLogger::getInstance().log(EventType::DamageTaken, target->getName(), getName(), getAttack());
		target->takeDamage(getAttack());
		g_sceneData.description += "먹물로 인해 배터리가 감소합니다! \n ";
		//std::cout << "먹물로 인해 배터리가 감소합니다!" << '\n';
		target->spendBattery(10);
	}

	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		//g_sceneData.description += getName() + "이 특수 공격을 사용했습니다! \n ";
		g_sceneData.description += getName() + "가 " + target->getName() + "의 공격을 모방합니다! \n ";
		//std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		//std::cout << getName() << "가 " << target->getName() << "의 공격을 모방합니다!" << '\n';
		int damage = target->getAttack();
		GameLogger::getInstance().log(EventType::DamageTaken, target->getName(), getName(), damage);
		target->takeDamage(damage);
	}

	void activatePassive() override
	{
		int rand = Random::getRandomValue(0, 100);

		if (rand <= 25)
		{
			g_sceneData.description += getName() + "의 패시브가 발동됩니다! \n ";
			g_sceneData.description += getName() + "가 다른 생물을 흉내냅니다! \n ";
			//std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
			//std::cout << getName() << "가 다른 생물을 흉내냅니다.!" << '\n';
			isMimic = true;
		}
		else
		{
			g_sceneData.description += getName() + "의 패시브가 발동되지 않았습니다. \n ";
			//std::cout << getName() << "의 패시브가 발동되지 않았습니다!" << '\n';
		}
	}
};

