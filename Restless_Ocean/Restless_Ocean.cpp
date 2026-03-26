// Restless_Ocean.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Monster.h"
#include "MonsterFactory.h"
#include "Player.h"
#include "BattleSystem.h"
#include "GameLogger.h"
void LoggingTest() {
    std::cout << "===============================" << '\n';
    std::cout << "로깅 및 출력 테스트." << '\n';
    GameLogger& logger = GameLogger::getInstance();
    // logger.log(현재 턴 수, EventType::이벤트 타입, 행동자, 대상자, 값(회복, 데미지 등));
    logger.log(1, EventType::Start, "테스터");
    logger.log(3, EventType::Move, "테스터", "유적1");
    logger.log(2, EventType::Battle, "테스터", "몬스터더미", 10);
    logger.log(2, EventType::Battle, "몬스터더미", "테스터", 10);
    logger.log(2, EventType::Kill, "테스터", "몬스터더미");
    logger.log(2, EventType::LevelUp, "테스터", 3);
    logger.log(3, EventType::ObtainItem, "테스터", "포션");
    logger.log(3, EventType::UseItem, "테스터", "포션");
    logger.log(3, EventType::Move, "테스터", "유적2");
    logger.log(4, EventType::Battle, "테스터", "보스더미", 10);
    logger.log(4, EventType::Battle, "보스더미", "테스터", 999);
    logger.log(4, EventType::Death, "테스터", "몬스터더미");
    logger.log(5, EventType::Return, "테스터");
    logger.printAllLogs();
    std::cout << "===============================" << '\n';
}

int main()
{
    std::cout << "Hello World!\n";

    MonsterFactory m;
    for (int i = 0; i < 10; ++i)
    {
        Monster* monster = m.GenerateMonster(1);
        monster->showStat();
    }

    // Battle System 테스트용
    //BattleSystem bs;
    //Player* player = new Player("나영");
    //gm.startBattleSequence(player);

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
