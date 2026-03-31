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
#include "GlobalVal.h"

Dungeon::Dungeon()
	: currentMap(GameManager::getInstance().createNextMap())
{
	if (!currentMap) {
		currentMap = std::make_unique<BuildingMap>();
	}
}
Dungeon::Dungeon(std::unique_ptr<IMap> map)
	: currentMap(std::move(map))
{
}
void Dungeon::start()
{

	// 현재 던전(맵) 정보를 출력하여 플레이어가 무기 선택 시 참고할 수 있도록 함
	g_sceneData.description = "던전에 입장했습니다. \n";
	g_sceneData.Title = "현재 던전: " + currentMap->GetName();


}

void Dungeon::update()
{
	int battleCountInDungeon = 0;
	Player& player = GameManager::getInstance().getPlayer();

	player.setWeapon(weaponManager.selectWeapon());

	// 5번의 전투를 마칠 때까지 루프

	while (battleCountInDungeon < 5)
	{
		battleCountInDungeon++;

		g_sceneData.Title = "현재 던전: " + currentMap->GetName() + "[" + std::to_string(battleCountInDungeon) + " / 5 단계]";
		BattleResult result = battleSystem.startBattleSequence(&player, currentMap->GetAttributeType());

		// 도망 쳤을 시 battleCount 초기화 및 로비 이동
		if (result == BattleResult::RunAway)
		{
			GameManager::getInstance().resetBattleCount();
			GameManager::getInstance().changeStage(std::make_unique<Lobby>());
			return;
		}
		std::cout << "================================" << std::endl;

		if (GameManager::getInstance().isGameEnded()) return;

		// 5번째 전투 보스전 승리 후, 현재 맵 클리어 기록 저장
		if (battleCountInDungeon == 5 && result == BattleResult::PlayerWin)
		{
			GameManager::getInstance().addClearMap(currentMap->GetMapType());

			if (player.hasAllArtifacts()) {
				GameManager::getInstance().endGame(GameOverReason::Clear);
				return;
			}
		}

		// 5번째 보스전이 끝났을 때만 선택지를 줍니다.
		if (battleCountInDungeon >= 5)
    {
    g_sceneData.description += "\n[알림] 이 구역의 모든 위협을 제거하고 유적을 확보했습니다!\n";
    g_sceneData.description += "1. 다음 유적지로 이동\n";
    g_sceneData.description += "2. 육지(로비)로 귀환\n";
    
    g_sceneData.options = { "다음 유적지로 이동", "육지(로비)로 복귀" };
    g_sceneData.selectedIndex = 0;

    int input = g_cliRenderer.OptionSelector(g_sceneData);

    if (input == 0) // '다음 유적지로 이동' 선택 시
    {
        std::unique_ptr<IMap> nextMap = GameManager::getInstance().createNextMap();

        if (nextMap != nullptr)
        {
            GameManager::getInstance().changeStage(std::make_unique<Dungeon>(std::move(nextMap)));
        }
        else
        {
            g_sceneData.description += "더 이상 탐험할 수 있는 유적이 없습니다.\n";
            GameManager::getInstance().changeStage(std::make_unique<Lobby>());
        }
        return;
    }
    else // '육지(로비)로 복귀' 선택 시
    {
        GameManager::getInstance().changeStage(std::make_unique<Lobby>());
        return;
    }
}

		// 5번이 안 끝났으면 선택지 없이 자동으로 다음 전투 진행
		g_sceneData.description = "[시스템] 심해를 더 깊이 탐사합니다... \n ";
		g_cliRenderer.render(g_sceneData);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Dungeon::exit()
{
	g_sceneData.description = "전투가 종료되었습니다 \n ";
	g_sceneData.description += "던전 탐사를 종료합니다.";
	g_cliRenderer.render(g_sceneData);
}
