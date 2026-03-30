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
#include "Random.h"


Dungeon::Dungeon()
	: currentMap(GameManager::getInstance().createNextMap())
{}
Dungeon::Dungeon(std::unique_ptr<IMap> map) : currentMap(std::move(map)) {}

void Dungeon::start()
{
	std::cout << "\n던전에 입장했습니다." << '\n';

	// 현재 던전(맵) 정보를 출력하여 플레이어가 무기 선택 시 참고할 수 있도록 함
	if (currentMap)
	{
		std::cout << "현재 던전: " << currentMap->GetName() << '\n';
	}

}

void Dungeon::update()
{
	int battleCountInDungeon = 0;
	Player& player = GameManager::getInstance().getPlayer();
	// 5번의 전투를 마칠 때까지 루프
	while (battleCountInDungeon < 5)
	{
		battleCountInDungeon++;

		std::cout << "\n================================" << std::endl;
		if (currentMap)
		{
			std::cout << "\n[" << currentMap->GetName() << " - " << battleCountInDungeon << " / 5 단계]" << std::endl;
		}
		else
		{
			std::cout << "\n[Unknown Map - " << battleCountInDungeon << " / 5 단계]" << std::endl;
		}
		std::cout << "================================" << std::endl;

		BattleResult result = battleSystem.startBattleSequence(&player, currentMap->GetAttributeType());
		if (GameManager::getInstance().isGameEnded()) return;

		if (result == BattleResult::RunAway)
		{
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
		}

		if (battleCountInDungeon >= 5)
		{
			std::cout << "\n[알림] 이 구역의 모든 위협을 제거하고 유적을 확보했습니다!" << std::endl;
			std::cout << "1. 다음 유적지로 이동 (랜덤)\n";
			std::cout << "2. 육지(로비)로 귀환\n";

			// 현재 맵 클리어 목록 추가
			GameManager::getInstance().addClearMap(currentMap->GetMapType());

			//유적 체크

			if (player.hasAllArtifacts()) {
				GameManager::getInstance().endGame(GameOverReason::Clear);
				return;
			}

			int input = InputSystem::getInputInt(1, 2);
			if (input == 1) {
				// 선택된 현재 맵과 다른 맵을 랜덤으로 선택
				auto nextMap = GameManager::getInstance().createNextMap();
				// 시도해서 다른 맵을 얻을 때까지 반복
				if (nextMap) {
					GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::move(nextMap)));
				}
				else {
					// 더 이상 갈 곳이 없다면 엔딩 혹은 로비로
					std::cout << "더 이상 탐사할 구역이 없습니다." << std::endl;
					GameManager::getInstance().changeStage(std::make_unique<Lobby>());
				}
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
