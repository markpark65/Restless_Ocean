#pragma once
#include "BossMonster.h"
#include "Player.h"
#include "Random.h"

class MimicOctopus : public BossMonster
{
private:
	bool isMimic = false;

public:
	MimicOctopus(const MonsterStat& stat) : BossMonster(stat) {}

	void takeDamage(int damage) override
	{
		if (isMimic)
		{
			std::cout << getName() << "가 흉내낸 대상을 공격하여 피해를 입지 않습니다!" << '\n';
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

		std::cout << getName() << "가 일반 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "가 먹물을 발사합니다!" << '\n';
		std::cout << getName() << "는 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
		std::cout << target->getName() << "는 먹물로 인해 배터리가 " << 10 << "% 감소됩니다" << '\n';
		target->spendBattery(10);
	}

	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "가 " << target->getName() << "의 공격을 모방합니다!" << '\n';
		int damage = target->getAttack();
		std::cout << "강력한 일격이 " << target->getName() << " 에게 " << damage << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(10);
	}

	void activatePassive() override
	{
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "가 다른 생물을 흉내냅니다.!" << '\n';
		isMimic = true;
	}
};

