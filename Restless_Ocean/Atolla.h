#pragma once
#include "BossMonster.h"
#include "Player.h"

class Atolla : public BossMonster
{
private:


public:
	Atolla(const MonsterStat& stat) : BossMonster(stat) {}

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
		std::cout << getName() << "가 일반 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "가 촉수로 공격합니다!" << '\n';
		std::cout << getName() << "는 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
		std::cout << getName() << "는 추가로 " << target->getName() << "에게 " << getAttack() << "의 독 데미지를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 0.2);
	}

	void useSpecialAttack(Player* target) override
	{
		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 빛을 모아 바로 폭발합니다!" << '\n';

		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() * 2 << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 2);
	}

	void activatePassive() override
	{
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
	}
};

