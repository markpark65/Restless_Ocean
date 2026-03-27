#include <iostream>

#include "Shop.h"
#include "Lobby.h"
#include "Dungeon.h"

#include "Player.h"
#include "Item.h"
#include "Inventory.h"

#include "GameManager.h"
#include "ShopSystem.h"
#include "InputSystem.h"


void Shop::start()
{
	std::cout << "\n상점으로 왔습니다." << '\n';
}

void Shop::update()
{
	// 상점 방문
	Player& player = GameManager::getInstance().getPlayer();
	

	while (true)
	{
		std::cout << "무엇을 하시겠습니까?" << '\n';
		std::cout << "1. 구매" << "\n";
		std::cout << "2. 판매" << "\n";
		std::cout << "3. 로비 이동" << "\n";
		std::cout << "4. 던전 입장" << "\n";
		std::cout << "5. 게임 종료" << "\n";

		int input = InputSystem::getInputInt(1, 5);

		switch (input)
		{
		case 1:
			shopSystem.buyItem(player);
			break;
		case 2:
			shopSystem.sellItem(player);
			break;
		case 3:
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
			break;
		case 4:
			GameManager::getInstance().changeStage(std::make_unique<Dungeon>());
			return;
			break;
		case 5:
			GameManager::getInstance().changeStage(nullptr);
			std::cout << "게임을 종료합니다.\n";
			return;
			break;
		default:
			std::cout << "잘못된 입력입니다.\n";
			continue;
		}

		std::cout << "\n";
	}
}

void Shop::exit()
{
	std::cout << "상점를 떠납니다." << '\n';
}
