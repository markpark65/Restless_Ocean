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

#include "GlobalVal.h"


void Shop::start()
{
	g_sceneData.description = "상점으로 왔습니다.";
	g_sceneData.Title = "Shop";
	//std::cout << "\n상점으로 왔습니다." << '\n';
}

void Shop::update()
{
	// 상점 방문
	Player& player = GameManager::getInstance().getPlayer();


	while (true)
	{
		g_sceneData.description += "";
		g_sceneData.sceneText = {
			 "무엇을 하시겠습니까?",
			 "1. 구매",
			 "2. 판매",
			 "3. 보유 아이템 확인",
			 "4. 무기 강화",
			 "5. 아이템 공방",
			 "6. 로비 이동",
			 "7. 게임 종료",
		};
		g_sceneData.selectedIndex = 0;
		g_sceneData.options = {
			 "구매",
			 "판매",
			 "보유 아이템 확인",
			 "무기 강화",
			 "아이템 공방",
			 "로비 이동",
			 "게임 종료"

		};
		//std::cout << "무엇을 하시겠습니까?"		<< '\n';
		//std::cout << "1. 구매"					 << "\n";
		//std::cout << "2. 판매"					 << "\n";
		//std::cout << "3. 보유 아이템 확인"		 << "\n";
		//std::cout << "4. 무기 강화"				 << "\n";
		//std::cout << "5. 아이템 공방"			<< "\n";
		//std::cout << "6. 로비 이동"				 << "\n";
		//std::cout << "7. 게임 종료"				 << "\n";

		int input = g_cliRenderer.OptionSelector(g_sceneData);
		//int input = InputSystem::getInputInt(1, 8);
		input += 1;
		switch (input)
		{
		case 1:
			shopSystem.buyItem(player);
			break;
		case 2:
			shopSystem.sellItem(player);
			break;
		case 3: {
			g_sceneData.description = "보유중인 아이템 \n ";
			g_sceneData.sceneText = {};
			g_sceneData.sceneText.push_back("=== 판매 === ");
			g_sceneData.sceneText.push_back("0: [상점으로 돌아가기]");
			g_sceneData.selectedIndex = 0;
			g_sceneData.options = { "상점으로 돌아가기" };
			//std::cout << "\n=== 판매 ===\n";
			//std::cout << "0: [상점으로 돌아가기]\n\n";
			int size = player.getInventory().getSize();

			if (player.getInventory().getSize() == 0) {
				g_sceneData.description = "보유한 아이템이 없습니다. \n ";
				return;
			}

			std::vector<std::string> items = player.getInventory().printAllstr();
			for (auto& it : items) {
				g_sceneData.sceneText.push_back(it);
				//g_sceneData.options.push_back(it);
			}
			g_cliRenderer.render(g_sceneData);
			std::cout << "판매할 아이템 번호 ";
			int input = g_cliRenderer.OptionSelector(g_sceneData);
			g_sceneData.description = "상점으로 돌아갑니다.";
			//player.getInventory().printAll();
			break;
		}
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
			GameManager::getInstance().changeStage(nullptr);
			std::cout << "게임을 종료합니다.\n";
			return;
			break;
		default:
			g_sceneData.description = "잘못된 입력입니다.";
			//std::cout << "잘못된 입력입니다.\n";
			continue;
		}

		std::cout << "\n";
	}
}

void Shop::exit()
{
	g_sceneData.description = "잘못된 입력입니다.";
	//std::cout << "상점를 떠납니다." << '\n';
}
