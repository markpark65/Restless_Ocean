#include <iostream>
#include "Monster.h"
#include "MonsterFactory.h"
#include "Player.h"
#include "Skill.h"
#include "BattleSystem.h"
#include "GameLogger.h"
#include "GameManager.h"
#include "Item.h"
#include "Inventory.h"
#include "GlobalVal.h"
void LoggingTest() {
    std::cout << "===============================" << '\n';
    std::cout << "로깅 및 출력 테스트." << '\n';
    GameLogger& logger = GameLogger::getInstance();
    // logger.log(EventType::이벤트 타입, 행동자, 대상자, 값(회복, 데미지 등));
	//						move이벤트를 제외한 actor파라미터를 플레이어로 고정했습니다.
    logger.log(EventType::Start,		"테스터");
    logger.log(EventType::Move,			"지상",			"유적1");		////구역 이동
    logger.log(EventType::DamageDealt,	"테스터",		"몬스터더미", 10);	//플레이어가 데미지 줄때
    logger.log(EventType::DamageTaken,	"테스터",		"몬스터더미", 10);	//플레이어가 데미지 받을때
    logger.log(EventType::Kill,			"테스터",		"몬스터");		//적 처치
    logger.log(EventType::LevelUp,		"테스터",		3);				//레벨 n으로 상승
	logger.log(EventType::ObtainItem, "테스터", "포션");			//아이템 획득
	logger.log(EventType::UseItem, "테스터", "포션");			//아이템 사용
	logger.log(EventType::ObtainGold, "테스터", 13);			//아이템 획득
	logger.log(EventType::UseGold, "테스터", 10);			//아이템 사용
    logger.log(EventType::Move,			"테스터",		"유적2");		//구역 이동
    logger.log(EventType::DamageDealt,	"테스터",		"보스더미",	10);
    logger.log(EventType::DamageTaken,	"테스터",		"보스더미",	999);
    logger.log(EventType::Death,		"테스터",		"보스더미");	//몬스터에게 사망 이벤트
    logger.log(EventType::Return,		"테스터");		//육지 귀환?
    logger.printAllLogs();
    std::cout << "===============================" << '\n';
}

void PrintStatisicsTest() {
	std::cout << "===============================" << '\n';
	GameStatistics& stat = GameStatistics::getInstance();
	stat.PrintStatistics();
	std::cout << "===============================" << '\n';
}
void printFootballFish() {

	std::cout <<
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
		<< '\n';
}

void printViperFish() {
	std::cout <<
		R"(
               __                 
           ,,/'                 
         ,','                   
    _...''/_.............._,.-,/
   \(_)                  _.  ,' 
\.__>   ,_____ _____..--''`-.,\ 
 ''''-'''      \`-.           ''
                `,'                       
)" << '\n';
}

void printGiantSquid() {
	cout << R"(
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
    )" << '\n';
}
int main()
{
	//콘솔 인코딩 UFT-8 with BOM으로 변경하여 깨짐 방지.
	//system("chcp 65001");
	//system("cls");
  //게임 실행
	//GameManager::getInstance().run();

	printFootballFish();

	return 0;
	
}
