#pragma once
#include <random>

#include "Monster.h"
#include "Slime.h"

class MonsterFactory
{
public:
	int returnRandomValue(int min, int max)
	{
		// 재사용 가능한 난수 엔진
		static std::mt19937 gen(std::random_device{}());
		// 플레이어 레벨에 따라 몬스터의 스탯 범위를 결정하기 위한 난수열
		std::uniform_int_distribution<int> dis(min, max);

		return dis(gen);
	}

	Monster* GenerateMonster()
	{
		int healthDis = returnRandomValue(20, 30);
		int attackDis = returnRandomValue(5, 10);

	}

};

