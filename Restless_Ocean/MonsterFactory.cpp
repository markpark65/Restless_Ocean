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
	MapType map;
	std::string asset;
};

static const MonsterTemplate normalTemplates[] =
{
	{ "초롱 아귀",		220, 250, 15, 18, 95, 105, AttributeType::Luminous,
		"\n- 패시브    : 공격력이 지속적으로 증가한다."
		"\n- 일반 공격 : 몸통 박치기로 공격한다."
		"\n- 특수 공격 : 빛을 축적해 다음 공격을 강화한다.",
	MapType::BuildingMap,
			R"(
   ,_,...   ____             
,,,.   ,/`''   ''`-..        
'..|  ,/  (_)       '\.      
      '...            `_     
  |--.__/'     _ ''`\ `.--''`.
   \_           '_  /        |
    `\_           '`,-"`._ ,J'
      '-..._____,,-'     '''  
        )"
	},

	{ "바이퍼 피쉬",	200, 230, 18, 22, 110, 120, AttributeType::Hidden, 
		"\n- 패시브    : 속도가 증가하며 기습 공격을 한다."
		"\n- 일반 공격 : 물어뜯기로 공격한다."
		"\n- 특수 공격 : 연속 공격으로 추가 피해를 입힌다.",
	MapType::SeaCaveMap,
	R"(
               __                 
           ,,/'                 
         ,','                   
    _...''/_.............._,.-,/
   \(_)                  _.  ,' 
\.__>   ,_____ _____..--''`-.,\ 
 ''''-'''      \`-.           ''
                `,'                       
)"
	},

	{ "대왕 오징어",	240, 270, 13, 16, 80, 90, AttributeType::Giant, 
		"\n- 패시브    : 체력을 회복한다."
		"\n- 일반 공격 : 먹물을 발사해 공격한다."
		"\n- 특수 공격 : 돌진하여 확률적으로 큰 피해를 입힌다.",
	MapType::CollapsedShipMap,
	R"(
    _,..                 .+-------...
   /'  ,|              __.`--''     .
   | .''           _,-''           /|
   , |.           |'             ,'.'
    \ '"___--__.--'''`\       ,,._ / 
     '',  ,_,       . |   __,-'   '  
  ,,Y'',/'' _   , _(■)''-''          
 /' ,Y' ,,-' ,, ['' '  _,..          
|,,'',,-',_.''|  '---'''  |          
''...._--'     `,_     _,-'          
                 '''''''               
    )"
	}
};

static const MonsterTemplate bossTemplates[] =
{
	{ "왕관 해파리",	400, 450, 27, 32, 100, 110, AttributeType::Luminous,
		"\n- 패시브    : 일반 공격의 독 피해량이 증가한다."
		"\n- 일반 공격 : 촉수 공격 후 독 피해를 추가로 입힌다."
		"\n- 특수 공격 : 빛을 모아 폭발시켜 큰 피해를 입힌다.",
	MapType::BuildingMap,
		R"(
        .-~~~~~~~~~~~~-.
     .-'                '-.
   .'                      '.
  /                          \
  \   __   __   __   __     /
   '._/ \_/  \_/  \_/ \___.'
      /     /   /     /
     /     /   /     /
    /     /   /     /
   /     /   /     /
    )"
	},

	{ "흉내 문어",		350, 400, 22, 27, 120, 130, AttributeType::Hidden, 
		"\n- 패시브    : 다른 생물을 흉내 내어 다음 공격을 무효화한다."
		"\n- 일반 공격 : 먹물을 발사하고 배터리를 감소시킨다."
		"\n- 특수 공격 : 상대의 공격을 모방해 큰 피해를 입힌다.",
	MapType::SeaCaveMap,
		R"(
               _,--._
             ,'      `.
     |\     / ,-.  ,-. \     /|
     )o),/ ( ( o )( o ) ) \.(o(
    /o/// /|  `-'  `-'  |\ \\\o\
   / / |\ \(   .    ,   )/ /| \ \
   | | \o`-/    `\/'    \-'o/ | |
   \ \  `,'              `.'  / /
\.  \ `-'  ,'|   /\   |`.  `-' /  ,/
 \`. `.__,' /   /  \   \ `.__,' ,'/
  \o\     ,'  ,'    `.  `.     /o/
   \o`---'  ,'        `.  `---'o/
    `.____,'	         `.____,'
)"

	},

	{ "레비아탄",		500, 550, 30, 35, 90, 100, AttributeType::Giant,
		"\n- 패시브    : 방어력이 증가하여 받는 피해를 줄인다."
		"\n- 일반 공격 : 물어 뜯기 및 대원의 압력을 감소시킨다."
		"\n- 특수 공격 : 거대한 물살로 끌어들여 큰 피해 및 대원의 압력을 감소시킨다.",
	MapType::CollapsedShipMap,
		R"(
          /           /
         /' .,,,,  ./
        /';'     ,/
       / /   ,,//,`'`
      ( ,, '_,  ,,,' ``
      |    /@  ,,, ;" `
     /    .   ,''/' `,``
    /   .     ./, `,, ` ;
 ,./  .   ,-,',` ,,/''\,'
|   /; ./,,'`,,'' |   |
|     /   ','    /    |
 \___/'   '     |     |
   `,,'  |      /     `\ 
    )"

	}
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
	if (mapType == AttributeType::Luminous) stat.map = MapType::BuildingMap;
	else if (mapType == AttributeType::Hidden) stat.map = MapType::SeaCaveMap;
	else if (mapType == AttributeType::Giant) stat.map = MapType::CollapsedShipMap;

	float hpStat = 1.0f + (level + 1) * 0.4f;
	float attackStat = 1.0f + (level + 1) * 0.2f;

	int stage = 0;
	if (battleCount > 0) {
		stage = (battleCount - 1) / 5;
	}

	float stageMultiplier = 1.0f + (stage * 0.2f);

	float levelHpMultiplier = 1.0f + ((level + 1) * 0.05f);
	float levelAtkMultiplier = 1.0f + ((level + 1) * 0.025f);

	stat.health = static_cast<int>(Random::getRandomValue(monsterTemplate->minHealth, monsterTemplate->maxHealth) * stageMultiplier * levelHpMultiplier); //hpStat);
	stat.attack = static_cast<int>(Random::getRandomValue(monsterTemplate->minAttack, monsterTemplate->maxAttack) * stageMultiplier * levelAtkMultiplier);
	stat.speed = Random::getRandomValue(monsterTemplate->minSpeed, monsterTemplate->maxSpeed);
	stat.type = monsterTemplate->type;
	stat.description = monsterTemplate->description;
	stat.map = monsterTemplate->map;
	stat.asset = monsterTemplate->asset;

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
