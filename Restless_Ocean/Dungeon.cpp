#include <iostream>
#include "Random.h"
#include "Lobby.h"
#include "Dungeon.h"
#include "Shop.h"
#include "BattleSystem.h"
#include "GameManager.h"
#include "Player.h"
#include "InputSystem.h"
//#include "BuildingMap.h"
//#include "SeaCaveMap.h"
//#include "CollapsedShipMap.h" //map class
#include "MapUtils.h" //enum class

void Dungeon::start()
{
	std::cout << "\n던전에 입장했습니다." << '\n';
}

void Dungeon::update()
{
	while (true)
	{
		//selectRandomMap();
		//std::cout << "\n현재 맵은 : " << GetMapName(currentMapType_) << "입니다.\n";//enum class
		//std::cout << "\n현재 맵은 : " << currentMap_->GetName() << "입니다.\n";//map class

		// to do: 배틀 시스템 로직 추가
		Player& player = GameManager::getInstance().getPlayer();
		battleSystem.startBattleSequence(&player);

		// 전투 종료 후
		std::cout << "무엇을 하시겠습니까?\n";
		std::cout << "1. 계속 탐험\n";
		std::cout << "2. 로비 이동\n";
		std::cout << "3. 상점 이용\n";
		std::cout << "4. 게임 종료\n";

		int input = InputSystem::getInputInt(1, 3);

		switch (input)
		{
		case 1:
			std::cout << "\n";
			continue;
		case 2:
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
			break;
		case 3:
			GameManager::getInstance().changeStage(std::make_unique<Shop>());
			return;
			break;
		case 4:
			GameManager::getInstance().changeStage(nullptr);
			std::cout << "게임을 종료합니다.\n";
			return;
			break;
		default:
			std::cout << "잘못된 입력입니다.\n";
			continue;
		}
	}
}

void Dungeon::exit()
{
	std::cout << "전투가 종료되었습니다" << '\n';
	std::cout << "던전을 나갑니다" << '\n';
}

//map 클래스 구현
//void Dungeon::selectRandomMap() {
//	int randomMap = Random::getRandomValue(0, 2);
//
//	switch (randomMap)
//	{
//	case 0:
//		currentMap_ = std::make_unique<BuildingMap>();
//		break;
//	case 1:
//		currentMap_ = std::make_unique<SeaCaveMap>();
//		break;
//	case 2:
//		currentMap_ = std::make_unique<CollapsedShipMap>();
//		break;
//	default:
//		break;
//	}
//}

//enum 클래스 구현
//void Dungeon::selectRandomMap()
//{
//	int randomValue = Random::getRandomValue(0, 2);
//	currentMapType_ = static_cast<MapType>(randomValue);
//}
