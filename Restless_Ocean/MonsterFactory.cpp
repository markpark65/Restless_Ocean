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
	{ "초롱 아귀",		15, 25, 5, 10, 95, 105, AttributeType::Luminous,
		"\n- 패시브    : 공격력이 지속적으로 증가한다."
		"\n- 일반 공격 : 몸통 박치기로 공격한다."
		"\n- 특수 공격 : 빛을 축적해 다음 공격을 강화한다."
	, Map::SeaCaveMap },

	{ "바이퍼 피쉬",	10, 20, 10, 15, 100, 110, AttributeType::Hidden,
		"\n- 패시브    : 속도가 증가하며 기습 공격을 한다."
		"\n- 일반 공격 : 물어뜯기로 공격한다." 
		"\n- 특수 공격 : 연속 공격으로 추가 피해를 입힌다.",
	Map::BuildingMap },

	{ "대왕 오징어",	25, 35, 5, 10, 90, 100, AttributeType::Giant,
		"\n- 패시브    : 체력을 회복한다."
		"\n- 일반 공격 : 먹물을 발사해 공격한다."
		"\n- 특수 공격 : 돌진하여 확률적으로 큰 피해를 입힌다.",
	Map::CollapsedShipMap }
};

static const MonsterTemplate bossTemplates[] =
{
	{ "왕관 해파리",	1, 2,  5, 10, 95, 105, AttributeType::Luminous,
		"\n- 패시브    : 강한 빛으로 적을 실명시켜 다음 턴 피해를 무효화한다."
		"\n- 일반 공격 : 촉수 공격 후 독 피해를 추가로 입힌다."
		"\n- 특수 공격 : 빛을 모아 폭발시켜 큰 피해를 입힌다.",
		Map::SeaCaveMap },

	{ "흉내 문어",		1, 2, 10, 15, 100, 110, AttributeType::Hidden,
		"\n- 패시브    : 다른 생물을 흉내 내어 다음 공격을 무효화한다."
		"\n- 일반 공격 : 먹물을 발사하고 배터리를 감소시킨다."
		"\n- 특수 공격 : 상대의 공격을 모방해 큰 피해를 입힌다.",
		Map::BuildingMap },

	{ "레비아탄",		1, 2, 10, 20, 90, 100, AttributeType::Giant,
		"\n- 패시브    : 방어력이 증가하여 받는 피해를 줄인다."
		"\n- 일반 공격 : 물어뜯기 및 대원의 압력을 감소시킨다."
		"\n- 특수 공격 : 거대한 물살로 끌어들여 큰 피해 및 대원의 압력을 감소시킨다.",
		Map::CollapsedShipMap }
};

// 플레이어 레벨에 따라 랜덤으로 몬스터의 스탯 조정
Monster* MonsterFactory::GenerateMonster(int level, int battleCount, AttributeType mapType)
{
	const MonsterTemplate* monsterTemplate = nullptr;
	int index = -1;

	bool isBossBattle = (battleCount > 0 && battleCount % 5 == 0);
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
