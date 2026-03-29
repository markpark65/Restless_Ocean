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

	// 8번의 전투를 마칠 때까지 루프
	while (battleCountInDungeon < 8)
	{
		battleCountInDungeon++;

		// [추가] 몇 번째 전투인지 출력 (원래 for문 로직 복구)
		std::cout << "\n================================" << std::endl;
		std::cout << "  [ " << battleCountInDungeon << " / 8 ] 단계 탐사 중..." << std::endl;
		std::cout << "================================" << std::endl;

		// [중요] 배틀 시스템에 현재 맵의 속성을 전달해야 몬스터가 맞게 나옵니다.
		// (BattleSystem의 startBattleSequence나 battle 함수가 AttributeType을 받도록 수정되어야 함)
		battleSystem.startBattleSequence(&player);

		if (GameManager::getInstance().isGameEnded()) return;

		// 8번째 보스전이 끝났을 때만 선택지를 줍니다.
		if (battleCountInDungeon >= 8)
		{
			std::cout << "\n[알림] 이 구역의 모든 위협을 제거하고 유적을 확보했습니다!" << std::endl;
			std::cout << "1. 다음 유적지로 이동\n";
			std::cout << "2. 육지(로비)로 귀환\n";

			int input = InputSystem::getInputInt(1, 2);
			if (input == 1) {
				// 다음 맵 설정 로직 (예: Building -> CollapsedShip)
				// 실제 구현 시에는 GameManager에서 다음 스테이지를 Dungeon(다음맵)으로 넘겨줘야 합니다.
				GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::make_unique<CollapsedShipMap>()));
				return;
			}
			else {
				GameManager::getInstance().changeStage(std::make_unique<Lobby>());
				return;
			}
		}

		// 8번이 안 끝났으면 선택지 없이 자동으로 다음 전투 진행
		std::cout << "\n[시스템] 심해를 더 깊이 탐사합니다..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Dungeon::exit()
{
	std::cout << "전투가 종료되었습니다" << '\n';
	std::cout << "던전을 나갑니다" << '\n';
}
