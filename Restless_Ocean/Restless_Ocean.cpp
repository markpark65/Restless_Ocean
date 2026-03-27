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
    // logger.log(현재 턴 수, EventType::이벤트 타입, 행동자, 대상자, 값(회복, 데미지 등));
    logger.log(1, EventType::Start,			u8"테스터");
    logger.log(3, EventType::Move, u8"테스터",		"유적1");		////구역 이동
    logger.log(2, EventType::DamageDealt,	u8"테스터",		u8"몬스터더미", 10);	//플레이어가 데미지 줄때
    logger.log(2, EventType::DamageTaken,	u8"몬스터더미",	u8"테스터", 10);	//플레이어가 데미지 받을때
    logger.log(2, EventType::Kill,			u8"테스터",		u8"몬스터");		//적 처치
    logger.log(2, EventType::LevelUp,		u8"테스터",		3);				//레벨 n으로 상승
    logger.log(3, EventType::ObtainItem,	u8"테스터",		u8"포션");			//아이템 획득
    logger.log(3, EventType::UseItem,		u8"테스터",		u8"포션");			//아이템 사용
    logger.log(3, EventType::Move,			u8"테스터",		u8"유적2");		//구역 이동
    logger.log(4, EventType::DamageDealt,	u8"테스터",		u8"보스더미", 10);
    logger.log(4, EventType::DamageTaken,	u8"보스더미",		u8"테스터",	999);
    logger.log(4, EventType::Death,			u8"테스터",		u8"몬스터더미");	//몬스터에게 사망
    logger.log(5, EventType::Return,		u8"테스터");						//육지 귀환?
    logger.printAllLogs();
    std::cout << "===============================" << '\n';
}

int main()
{
	//콘솔 인코딩 UFT-8 with BOM으로 변경하여 깨짐 방지.
	system("chcp 65001");
	
	LoggingTest();
    //std::cout << "Hello World!\n";

    //MonsterFactory m;
    //for (int i = 0; i < 10; ++i)
    //{
    //    Monster* monster = m.GenerateMonster(1);
    //    monster->showStat();
    //}

    // Battle System 테스트용
    //BattleSystem bs;
    //Player* player = new Player("나영");
    //gm.startBattleSequence(player);

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
