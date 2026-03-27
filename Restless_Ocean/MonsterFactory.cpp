#include "MonsterFactory.h"
#include "Item.h"
#include "DataType.h"
#include "Random.h"

struct MonsterTemplate
{
	std::string name;
	int minHealth;
	int maxHealth;
	int minAttack;
	int maxAttack;
	int minSpeed;
	int maxSpeed;
	AttributeType type;
	std::string description;
	Map map;
};

static const MonsterTemplate normalTemplates[] =
{
	{ "초롱 아귀",		15, 25, 5, 10, 95, 105, AttributeType::Luminous, "초롱 아귀 설명", Map::SeaCaveMap },
	{ "바이퍼 피쉬",	10, 20, 10, 15, 100, 110, AttributeType::Hidden, "바이퍼 피쉬 설명", Map::BuildingMap },
	{ "대왕 오징어",	25, 35, 5, 10, 90, 100, AttributeType::Giant, "대왕 오징어 설명", Map::CollapsedShipMap }
};

static const MonsterTemplate bossTemplates[] =
{
	{ "왕관 해파리",	30, 50,  5, 10, 95, 105, AttributeType::Luminous, "왕관 해파리 설명", Map::SeaCaveMap },
	{ "흉내 문어",		20, 40, 10, 15, 100, 110, AttributeType::Hidden, "흉내 문어 설명", Map::BuildingMap },
	{ "레비아탄",		50, 70, 10, 20, 90, 100, AttributeType::Giant, "레비아탄 설명", Map::CollapsedShipMap }
};

// 플레이어 레벨에 따라 랜덤으로 몬스터의 스탯 조정
Monster* MonsterFactory::GenerateMonster(int level, int battleCount)
{
	const MonsterTemplate* monsterTemplate = nullptr;

	bool isBossBattle = (battleCount > 7);
	if (!isBossBattle)
	{
		int index = Random::getRandomValue(0, 2);
		monsterTemplate = &normalTemplates[index];
	}
	else
	{
		int index = Random::getRandomValue(0, 2);
		monsterTemplate = &bossTemplates[index];
	}

	MonsterStat stat;
	stat.name = monsterTemplate->name;
	stat.health = Random::getRandomValue(monsterTemplate->minHealth, monsterTemplate->maxHealth) * level;
	stat.attack = Random::getRandomValue(monsterTemplate->minAttack, monsterTemplate->maxAttack) * level;
	stat.speed = Random::getRandomValue(monsterTemplate->minSpeed, monsterTemplate->maxSpeed);
	stat.type = monsterTemplate->type;
	stat.description = monsterTemplate->description;
	stat.map = monsterTemplate->map;

	if (!isBossBattle)
		return new NormalMonster(stat);
	else
		return new BossMonster(stat);
}
