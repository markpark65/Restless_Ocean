#pragma once

#include "NormalMonster.h"
#include "Player.h"

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
			std::cout << getName() << "가 축적한 빛을 폭발시킵니다!" << '\n';
			target->takeDamage(damage);
		}
		else
		{
			std::cout << getName() << "이 일반 공격을 사용했습니다!" << '\n';
			std::cout << getName() << "이 몸통 박치기를 사용합니다!" << '\n';
			target->takeDamage(getAttack());
		}
	}
	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "가 빛을 모아 폭발을 준비합니다!" << '\n';
		readyExplode = true;
	}

	void activatePassive() override
	{
		int enhancedAttack = 10;
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "의 공격력이 " << enhancedAttack << "만큼 증가합니다" << '\n';
		setAttack(getAttack() + enhancedAttack);
	}

	void setAttack(int attack)
	{
		monsterStat.attack = attack;
	}
};

