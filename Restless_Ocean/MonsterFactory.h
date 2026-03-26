#pragma once
#include <random>

#include "Monster.h"

class MonsterFactory
{
public:
	// min ~ max 범위의 int 값 출력
	int getRandomValue(int min, int max);
	// 랜덤 몬스터 생성
	Monster* GenerateMonster(int level = 1);
};

