#pragma once
#include <random>
#include "IMap.h"
#include "Monster.h"
#include "BossMonster.h"
#include "NormalMonster.h"

class MonsterFactory
{
public:
	Monster* GenerateMonster(int level, int battleCount, AttributeType mapType);
};

