#include <iostream>
#include <thread>
#include <chrono>
#include "Lobby.h"
#include "Shop.h"
#include "Dungeon.h"
#include "GameManager.h"
#include "Player.h"
#include "InputSystem.h"
#include "BuildingMap.h"
#include "CollapsedShipMap.h"
#include "SeaCaveMap.h"

Dungeon::Dungeon() : currentMap(std::make_unique<BuildingMap>()) {}

Dungeon::Dungeon(std::unique_ptr<IMap> map) : currentMap(std::move(map)) {}

void Dungeon::start()
{
	std::cout << "\n던전에 입장했습니다." << '\n';

	// 현재 던전(맵) 정보를 출력하여 플레이어가 무기 선택 시 참고할 수 있도록 함
	std::cout << "현재 던전: " << currentMap->GetName() << '\n';

}

void Dungeon::update()
{
	int battleCountInDungeon = 0;
	Player& player = GameManager::getInstance().getPlayer();
	AttributeType mapType = currentMap->GetAttributeType();

	player.setWeapon(weaponManager.selectWeapon());
	cout << '\n';
	// 5번의 전투를 마칠 때까지 루프
	while (battleCountInDungeon < 5)
	{
		battleCountInDungeon++;

		// [추가] 몇 번째 전투인지 출력 (원래 for문 로직 복구)
		std::cout << "\n================================" << std::endl;
		std::cout << "\n[" << currentMap->GetName() << " - " << battleCountInDungeon << " / 5 단계]" << std::endl;
		std::cout << "================================" << std::endl;

		BattleResult result = battleSystem.startBattleSequence(&player, currentMap->GetAttributeType());

		// 도망 쳤을 시 battleCount 초기화 및 로비 이동
		if (result == BattleResult::RunAway)
		{
			GameManager::getInstance().resetBattleCount();
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
		}
		std::cout << "================================" << std::endl;

		BattleResult result = battleSystem.startBattleSequence(&player, currentMap->GetAttributeType());


		if (GameManager::getInstance().isGameEnded()) return;

		if (result == BattleResult::RunAway)
		{
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
		}

		// 5번째 전투 보스전 승리 후, 현재 맵 클리어 기록 저장
		if (battleCountInDungeon == 5 && result == BattleResult::PlayerWin)
		{
			GameManager::getInstance().addClearMap(currentMap->GetMapType());
		}

		// 5번째 보스전이 끝났을 때만 선택지를 줍니다.
		if (battleCountInDungeon >= 5)
		{
			std::cout << "\n[알림] 이 구역의 모든 위협을 제거하고 유적을 확보했습니다!" << std::endl;
			std::cout << "1. 다음 유적지로 이동\n";
			std::cout << "2. 육지(로비)로 귀환\n";
			int input = InputSystem::getInputInt(1, 2);
			if (input == 1) {
				//GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::make_unique<CollapsedShipMap>()));
				// 빌딩 -> 동굴 -> 탐사선 
				std::unique_ptr<IMap> nextMap = GameManager::getInstance().createNextMap();

				if (nextMap == nullptr)
				{
					std::cout << "더 이상 탐험할 수 있는 유적이 없습니다.\n";
					GameManager::getInstance().changeStage(std::make_unique<Lobby>());
					return;
				}

				GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::move(nextMap)));
				return;
			}
			else {
				GameManager::getInstance().changeStage(std::make_unique<Lobby>());
				return;
			}
		}

		// 5번이 안 끝났으면 선택지 없이 자동으로 다음 전투 진행
		std::cout << "\n[시스템] 심해를 더 깊이 탐사합니다..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Dungeon::exit()
{
	std::cout << "전투가 종료되었습니다" << std::endl;
	std::cout << "던전 탐사를 종료합니다." << std::endl;
}
