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
	//Player& player = GameManager::getInstance().getPlayer();
	//
	//ShopSystem shopSystem;
	//shopSystem.openShop(player, );
	//

	// 
	while (true)
	{
		std::cout << "무엇을 하시겠습니까?\n";
		std::cout << "1. 로비 이동\n";
		std::cout << "2. 던전 입장\n";
		std::cout << "3. 게임 종료\n";

		int input = InputSystem::getInputInt(1, 3);

		switch (input)
		{
		case 1:
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
			break;
		case 2:
			GameManager::getInstance().changeStage(std::make_unique<Dungeon>());
			return;
			break;
		case 3:
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

void Shop::exit()
{
	std::cout << "상점를 떠납니다." << '\n';
}
