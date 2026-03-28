#pragma once
#include "BossMonster.h"
#include "Player.h"
#include "Random.h"

class Atolla : public BossMonster
{
private:
	bool isHidden = false;

public:
	Atolla(const MonsterStat& stat) : BossMonster(stat) {}

	void takeDamage(int damage) override
	{
		if (isHidden)
		{
			std::cout << "하지만 실명으로 인해 << " << getName() << "는 데미지를 입지 않습니다!" << '\n';
			isHidden = false;
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
		std::cout << getName() << "가 촉수로 찌릅니다!" << '\n';
		std::cout << getName() << "는 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
		std::cout << getName() << "는 추가로 " << target->getName() << "에게 " << getAttack() << "의 독 데미지를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 0.2);
	}

	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 빛을 모아 폭발합니다!" << '\n';

		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() * 2 << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 2);
	}

	void activatePassive() override
	{
		int randomValue = Random::getRandomValue(0, 9);

		if (randomValue < 7)
		{
			std::cout << getName() << "의 패시브는 발동되지 않았습니다!" << '\n';
		}
		else
		{
			std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
			std::cout << getName() << "의 몸이 강하게 빛나 플레이어를 실명합니다." << '\n';
			std::cout << getName() << "는 다음 턴 데미지를 입지 않습니다." << '\n';
			isHidden = true;
		}
	}
};

