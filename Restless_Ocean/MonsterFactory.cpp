#include "MonsterFactory.h"
#include "Item.h"
#include "DataType.h"
#include "Random.h"

#include "FootballFish.h"
#include "ViperFish.h"
#include "GiantSquid.h"
#include "Atolla.h"
#include "MimicOctopus.h"
#include "Leviathan.h"

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
	{ "왕관 해파리",	1, 2,  5, 10, 95, 105, AttributeType::Luminous, "왕관 해파리 설명", Map::SeaCaveMap },
	{ "흉내 문어",		1, 2, 10, 15, 100, 110, AttributeType::Hidden, "흉내 문어 설명", Map::BuildingMap },
	{ "레비아탄",		1, 2, 10, 20, 90, 100, AttributeType::Giant, "레비아탄 설명", Map::CollapsedShipMap }
};

// 플레이어 레벨에 따라 랜덤으로 몬스터의 스탯 조정
Monster* MonsterFactory::GenerateMonster(int level, int battleCount, AttributeType mapType)
{
	const MonsterTemplate* monsterTemplate = nullptr;
	int index = -1;

	bool isBossBattle = (battleCount > 0 && battleCount % 8 == 0);
	const auto& templates = isBossBattle ? bossTemplates : normalTemplates;
	for (int i = 0; i < 3; ++i) {
        if (templates[i].type == mapType) {
            index = i;
            monsterTemplate = &templates[i];
            break;
        }
    }

	if (monsterTemplate == nullptr) {
		index = 0;
		monsterTemplate = &templates[0];
		// 로그 출력 (디버깅용)
		std::cout << "[경고] 일치하는 맵 속성을 찾지 못해 기본 몬스터를 생성합니다." << std::endl;
	}

	MonsterStat stat; stat.name = monsterTemplate->name;
	//출현지 문제 해결
	if (mapType == AttributeType::Luminous) stat.map = Map::SeaCaveMap;
	else if (mapType == AttributeType::Hidden) stat.map = Map::BuildingMap;
	else if (mapType == AttributeType::Giant) stat.map = Map::CollapsedShipMap;

	stat.health = Random::getRandomValue(monsterTemplate->minHealth, monsterTemplate->maxHealth) * level;
	stat.attack = Random::getRandomValue(monsterTemplate->minAttack, monsterTemplate->maxAttack) * level;
	stat.speed = Random::getRandomValue(monsterTemplate->minSpeed, monsterTemplate->maxSpeed);
	stat.type = monsterTemplate->type; stat.description = monsterTemplate->description; stat.map = monsterTemplate->map;

	if (!isBossBattle)
	{
		switch (index)
		{
			case 0: return new FootballFish(stat);
			case 1: return new ViperFish(stat);
			case 2: return new GiantSquid(stat);
		}
	}
	else
	{
		switch (index)
		{
			case 0: return new Atolla(stat);
			case 1: return new MimicOctopus(stat);
			case 2: return new Leviathan(stat);
		}
	}
	return nullptr;
}
