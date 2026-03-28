#pragma once

#include "NormalMonster.h"
#include "Player.h"

class ViperFish : public NormalMonster
{
public:
	ViperFish(const MonsterStat& stat) : NormalMonster(stat) {}

	void useBasicAttack(Player* target) override
	{
		std::cout << getName() << "이 일반 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 물어 뜯기를 사용합니다!" << '\n';
		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
	}

	void useSpecialAttack(Player* target) override
	{
		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 연속 물어 뜯기를 사용합니다!" << '\n';

		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 0.5);
		std::cout << getName() << "이 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack() * 0.25);
	}

	void activatePassive() override
	{
		int enhancedSpeed = 10;
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "는 은신하다 기습 공격을 합니다!" << '\n';
		std::cout << getName() << "의 스피드가 " << enhancedSpeed << "만큼 빨라집니다." << '\n';
	}

	void setSpeed(int speed)
	{
		monsterStat.speed = speed;
	}
};
