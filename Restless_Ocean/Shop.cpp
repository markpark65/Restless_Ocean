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
		std::cout << "3. 보유 아이템 확인" << "\n";
		std::cout << "4. 무기 강화" << "\n";
		std::cout << "5. 아이템 공방" << "\n";
		std::cout << "6. 로비 이동" << "\n";
		std::cout << "7. 던전 입장" << "\n";
		std::cout << "8. 게임 종료" << "\n";

		int input = InputSystem::getInputInt(1, 8);

		switch (input)
		{
		case 1:
			shopSystem.buyItem(player);
			break;
		case 2:
			shopSystem.sellItem(player);
			break;
		case 3:
			player.getInventory().printAll();
			break;
		case 4:
			shopSystem.enhanceWeapon(player);
			break;
		case 5:
			shopSystem.craftItem(player);
			break;
		case 6:
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
			break;
		case 7:
			GameManager::getInstance().changeStage(std::make_unique<Dungeon>());
			return;
			break;
		case 8:
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
