#pragma once
#include <random>

#include "Monster.h"
#include "BossMonster.h"
#include "NormalMonster.h"

class MonsterFactory
{
public:
	// min ~ max 범위의 int 값 출력
	int getRandomValue(int min, int max);
	// 랜덤 몬스터 생성
	Monster* GenerateMonster(int level = 1);
	Monster* GenerateBossMonster(int level = 1);
};

