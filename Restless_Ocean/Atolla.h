#pragma once
#include "BossMonster.h"
#include "Player.h"
#include "Random.h"

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

		std::cout << getName() << "가 일반 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "가 촉수로 찌릅니다!" << '\n';
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

		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 빛을 모아 폭발합니다!" << '\n';

		target->takeDamage(getAttack() * 2);
	}

	void activatePassive() override
	{
		poisionDamage += 0.1f;
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "의 독 데미지가 " << 0.1 << "배 증가합니다!" << '\n';
	}
};

