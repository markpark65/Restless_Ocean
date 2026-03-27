// Restless_Ocean.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Monster.h"
#include "MonsterFactory.h"
#include "Player.h"
#include "BattleSystem.h"
#include "GameLogger.h"
#include "GameManager.h"

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

int main()
{
	//콘솔 인코딩 UFT-8 with BOM으로 변경하여 깨짐 방지.
	system("chcp 65001");
	system("cls");
	//LoggingTest();
	//PrintStatisicsTest();
    //std::cout << "Hello World!\n";

    //MonsterFactory m;
    //for (int i = 0; i < 10; ++i)
    //{
    //    Monster* monster = m.GenerateMonster(1);
    //    monster->showStat();
    //}


	//GameManager::getInstance().run();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
