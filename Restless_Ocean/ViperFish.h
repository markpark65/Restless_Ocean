#pragma once

#include "NormalMonster.h"
#include "Player.h"
#include "GlobalVal.h"
class ViperFish : public NormalMonster
{
public:
	ViperFish(const MonsterStat& stat) : NormalMonster(stat) {}

	void useBasicAttack(Player* target) override
	{
		g_sceneData.description += getName() + "이 물어 뜯기를 사용합니다! \n ";

		target->takeDamage(getAttack());
	}

	void useSpecialAttack(Player* target) override
	{
		g_sceneData.description += getName() + "이 연속 물어 뜯기를 사용합니다! \n ";


		target->takeDamage(getAttack());
		target->takeDamage(static_cast<int>(getAttack() * 0.5));
		target->takeDamage(static_cast<int>(getAttack() * 0.25));
	}

	void activatePassive() override
	{
		int enhancedSpeed = 10;
		g_sceneData.description += getName() + "의 패시브가 발동됩니다! \n ";
		g_sceneData.description += getName() + "의 스피드가 " + std::to_string(enhancedSpeed) + "만큼 빨라집니다! \n ";
		g_sceneData.description += getName() + "는 은닉 후, 기습 공격을 합니다! \n ";
		setSpeed(getSpeed() + enhancedSpeed);
	}

	void setSpeed(int speed)
	{
		monsterStat.speed = speed;
	}
};
