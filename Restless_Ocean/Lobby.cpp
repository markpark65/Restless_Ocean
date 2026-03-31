#include <iostream>

#include "Lobby.h"
#include "Player.h"
#include "GameManager.h"
#include "Dungeon.h"
#include "Shop.h"
#include "InputSystem.h"
#include "Random.h"
#include "BuildingMap.h"
#include "CollapsedShipMap.h"
#include "SeaCaveMap.h"
#include "GlobalVal.h"

void Lobby::start()
{
	Player& player = GameManager::getInstance().getPlayer();
	g_sceneData.description = "로비로 돌아왔습니다. \n ";
	g_sceneData.Title = "Lobby";
	g_sceneData.sceneText = {};
	if (player.getHp() < player.getMaxHp()) {
		player.recoverDamage(player.getMaxHp()); //체력 초기화
		//std::cout << player.getName() << " 대원의 체력이 모두 회복되었습니다." << '\n';
		g_sceneData.description += player.getName() + " 대원의 체력이 모두 회복되었습니다. \n ";
	}

	if (player.getOxygen() < 100) {
		player.recoverOxygen(100); // 산소 초기화
		//std::cout << "산소가 재충전되었습니다. (100%)" << '\n';
		g_sceneData.description += "산소가 재충전되었습니다. (100%) \n ";
	}

	if (player.getPressure() > 0) {
		player.recoverPressure(player.getPressure()); // 압력 초기화 함수
		player.resetSpeed(); //
		//std::cout << "수압 장치가 초기화되었습니다. (0%)" << '\n';
		g_sceneData.description += "수압 장치가 초기화되었습니다. (0%) \n ";
	}
	if (player.getBattery() < 100) {
		player.rechargeBattery(100); // 100으로 설정하는 함수
		//std::cout << "배터리가 완충되었습니다. (100%)\n";
		g_sceneData.description += "배터리가 완충되었습니다. (100%) \n ";
	}
	//std::cout << "\n로비로 왔습니다." << '\n';
}

void Lobby::update()
{
	g_sceneData.monster = nullptr;
	g_sceneData.player = &GameManager::getInstance().getPlayer();
	g_sceneData.description += "안녕하세요. " + GameManager::getInstance().getPlayer().getName() + "님, 무엇을 하시겟습니까?";
	g_sceneData.options = {
		"던전 입장",
		"상점 이용",
		"게임 종료",
	};
	//std::cout << "안녕하세요. " << GameManager::getInstance().getPlayer().getName() << "님," << '\n';

	//std::cout << "무엇을 하시겠습니까?\n";
	//std::cout << "1. 던전 입장\n";
	//std::cout << "2. 상점 이용\n";
	//std::cout << "3. 게임 종료\n";

	while (true)
	{
		g_cliRenderer.render(g_sceneData);
		int selectedIndex = g_cliRenderer.OptionSelector(g_sceneData);
		switch(selectedIndex)
		{
		case 0:
		{
			//// 1. 0~2 사이의 랜덤 값을 뽑습니다.
			//int randomMapIdx = Random::getRandomValue(0, 2);
			//std::unique_ptr<IMap> selectedMap;
			//// 2. 숫자에 따라 실제 맵 객체를 생성합니다.
			//if (randomMapIdx == 0) {
			//	selectedMap = std::make_unique<SeaCaveMap>();
			//}
			//else if (randomMapIdx == 1) {
			//	selectedMap = std::make_unique<BuildingMap>();
			//}
			//else {
			//	selectedMap = std::make_unique<CollapsedShipMap>();
			//}
			//// 3. 생성한 맵을 Dungeon 생성자에 넘겨줍니다.
			//GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::move(selectedMap)));
			auto selectedMap = GameManager::getInstance().createNextMap();

			if (selectedMap) {
				// 인자가 있는 생성자 Dungeon(std::unique_ptr<IMap> map)를 호출하게 됩니다.
				GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::move(selectedMap)));
			}
			else {
				std::cout << "모든 유적을 이미 수집했습니다!\n";
			}
			return;
		}
		break;

		case 1:
			GameManager::getInstance().changeStage(std::make_unique<Shop>());
			return;
			break;

		case 2:
			GameManager::getInstance().changeStage(nullptr);
			std::cout << "게임을 종료합니다.\n";
			return;
			break;

		default:
			//std::cout << "잘못된 입력입니다.\n";
			continue;
		}
	}
}

void Lobby::exit()
{
	//std::cout << "로비를 떠납니다." << '\n';
}
