#include <iostream>
#include "Monster.h"
#include "MonsterFactory.h"
#include "Player.h"
#include "BattleSystem.h"
#include "GameLogger.h"
#include "GameManager.h"
#include "Item.h"
#include"Inventory.h"

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
    MonsterFactory m;
    for (int i = 0; i < 10; ++i)
    {
        Monster* monster = m.GenerateMonster(1);
        monster->showStat();
    }


	GameManager::getInstance().run();

	//BattleSystem 테스트
	BattleSystem battleSystem;
	Player* player = new Player("테스터");
	battleSystem.startBattleSequence(player);
}
