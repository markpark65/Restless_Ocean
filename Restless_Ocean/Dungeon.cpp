#include <iostream>

#include "Lobby.h"
#include "Shop.h"
#include "Dungeon.h"
#include "GameManager.h"
#include "Player.h"
#include "InputSystem.h"

void Dungeon::start()
{
	std::cout << "\n던전에 입장했습니다." << '\n';
}

void Dungeon::update()
{
	while (true)
	{
		// to do: 배틀 시스템 로직 추가
		Player& player = GameManager::getInstance().getPlayer();
		battleSystem.startBattleSequence(&player);

		if (GameManager::getInstance().isGameEnded())
		{
			return;
		}

		// 전투 종료 후
		std::cout << "무엇을 하시겠습니까?\n";
		std::cout << "1. 계속 탐험\n";
		std::cout << "2. 로비 이동\n";
		std::cout << "3. 상점 이용\n";
		std::cout << "4. 게임 종료\n";

		int input = InputSystem::getInputInt(1, 4);

		switch (input)
		{
		case 1:
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
