#include "MonsterFactory.h"
#include "Item.h"
#include "DataType.h"

int MonsterFactory::getRandomValue(int min, int max)
{
	// 재사용 가능한 난수 엔진
	static std::mt19937 gen(std::random_device{}());
	// 플레이어 레벨에 따라 몬스터의 스탯 범위를 결정하기 위한 난수열
	std::uniform_int_distribution<int> dis(min, max);

	return dis(gen);
}

// 플레이어 레벨에 따라 랜덤으로 몬스터의 스탯 조정
Monster* MonsterFactory::GenerateMonster(int level)
{
	MonsterStat stat;

	int randomType = getRandomValue(0, 2);

	switch (randomType)
	{
	case 0:
		stat.name = "초롱 아귀";
		stat.health = getRandomValue(22, 28) * level;
		stat.attack = getRandomValue(6, 9) * level;
		stat.speed = getRandomValue(95, 105);
		stat.type = AttributeType::Luminous;
		stat.description = "초롱 아귀";
		stat.map = Map::SeaCaveMap;
		break;
	case 1:
		stat.name = "바이퍼 피쉬";
		stat.health = getRandomValue(18, 24) * level;
		stat.attack = getRandomValue(7, 11) * level;
		stat.speed = getRandomValue(105, 115);
		stat.type = AttributeType::Hidden;
		stat.description = "바이퍼 피쉬";
		stat.map = Map::BuildingMap;
		break;
	case 2:
		stat.name = "대왕 오징어";
		stat.health = getRandomValue(28, 36) * level;
		stat.attack = getRandomValue(8, 12) * level;
		stat.speed = getRandomValue(80, 90);
		stat.type = AttributeType::Giant;
		stat.description = "대왕 오징어";
		stat.map = Map::CollapsedShipMap;
		break;
	default:
		return nullptr;
		break;
	}

	return new NormalMonster(stat);
}

Monster* MonsterFactory::GenerateBossMonster(int level)
{
	MonsterStat stat;

	int randomType = getRandomValue(0, 2);

	switch (randomType)
	{
	case 0:
		stat.name = "왕관 해파리";
		stat.health = getRandomValue(22, 28) * level;
		stat.attack = getRandomValue(6, 9) * level;
		stat.speed = getRandomValue(95, 105);
		stat.type = AttributeType::Luminous;
		stat.description = "왕관 해파리";
		stat.map = Map::SeaCaveMap;
		break;
	case 1:
		stat.name = "흉내 문어";
		stat.health = getRandomValue(18, 24) * level;
		stat.attack = getRandomValue(7, 11) * level;
		stat.speed = getRandomValue(105, 115);
		stat.type = AttributeType::Hidden;
		stat.description = "흉내 문어";
		stat.map = Map::BuildingMap;
		break;
	case 2:
		stat.name = "레비아탄";
		stat.health = getRandomValue(28, 36) * level;
		stat.attack = getRandomValue(8, 12) * level;
		stat.speed = getRandomValue(80, 90);
		stat.type = AttributeType::Giant;
		stat.description = "레비아탄";
		stat.map = Map::CollapsedShipMap;
		break;
	default:
		return nullptr;
		break;
	}

	return new BossMonster(stat);
}
