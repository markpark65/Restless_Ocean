#include "GameManager.h"
#include "Stage.h"
#include "Lobby.h"
#include "InputSystem.h"
#include "BattleSystem.h"
#include "IMap.h"
#include "BuildingMap.h"
#include "CollapsedShipMap.h"
#include "SeaCaveMap.h"
#include "GlobalVal.h"

Player& GameManager::getPlayer()
{
	return *player;
}

GameManager::GameManager()
	//: player(createPlayer())
{
	player = std::make_unique<Player>(createPlayer());
}

std::string GameManager::createPlayer()
{
	std::cout << "생성할 캐릭터의 이름을 입력하세요." << '\n';

	std::string name = InputSystem::getInputStr();
	return name;
}

void GameManager::resetBattleCount()
{
	battleCount = 1;
}


bool GameManager::hasClearMap(MapType mapType) const
{
	for (MapType clearedMap : clearMaps)
	{
		if (clearedMap == mapType)
		{
			return true;
		}
	}
	return false;
}

void GameManager::addClearMap(MapType mapType)
{
	if (!hasClearMap(mapType))
	{
		clearMaps.push_back(mapType);
	}
}

std::unique_ptr<IMap> GameManager::createNextMap() const
{
	if (!hasClearMap(MapType::BuildingMap))
	{
		return std::make_unique<BuildingMap>();
	}
	if (!hasClearMap(MapType::CollapsedShipMap))
	{
		return std::make_unique<CollapsedShipMap>();
	}
	if (!hasClearMap(MapType::SeaCaveMap))
	{
		return std::make_unique<SeaCaveMap>();
	}

	return nullptr;
}

void GameManager::setIsPlayerExit(bool playerExit)
{
	isPlayerExit = playerExit;
}

void GameManager::changeStage(std::unique_ptr<Stage> newStage)
{
	if (currentStage != nullptr)
	{
		currentStage->exit();
	}

	currentStage = std::move(newStage);

	if (currentStage != nullptr)
	{
		currentStage->start();
	}
}

void GameManager::run()
{
	while (true)
	{
		isGameOver = false;
		GameManager::getInstance().changeStage(std::make_unique<Lobby>());

		while (currentStage && !isGameOver)
		{
			currentStage->update();
		}

		if (isPlayerExit)
		{
			break;
		}

		std::cout << '\n';
		std::cout << "게임을 다시 시작하시겠습니까?" << '\n';
		std::cout << "1. 처음부터 다시 시작" << '\n';
		std::cout << "2. 게임 종료" << '\n';
		std::cout << "> ";
		g_sceneData.monster = nullptr;
		g_sceneData.Title = "Continue?";
		g_sceneData.description = "게임을 다시 시작하시겟습니까?";
		g_sceneData.options = {
			"처음부터 다시 시작",
			"게임 종료"
		};

		//int input = InputSystem::getInputInt(1, 2);
		int input = g_cliRenderer.OptionSelector(g_sceneData);
		input += 1;
		if (input == 1)
		{
			resetGameState();
		}
		else
		{
			break;
		}
	}
}

void GameManager::endGame(GameOverReason reason)
{
	isGameOver = true;

	if (reason == GameOverReason::Clear)
	{
		g_sceneData.sceneText = {
			"================================",
			"모든 유적을 모았습니다!",
			"심해의 비밀이 드러납니다.",
			"(대충 왕국과 심해어들의 비밀)",
			"게임을 종료합니다.",
			"================================",
		};
		//std::cout << "\n================================" << '\n';
		//std::cout << "모든 유적을 모았습니다!" << '\n';
		//std::cout << "심해의 비밀이 드러납니다." << '\n';
		//std::cout << "(대충 왕국과 심해어들의 비밀)" << '\n';
		//std::cout << "게임을 종료합니다." << '\n';
		//std::cout << "================================" << '\n';
	}
	else
	{
		g_sceneData.sceneText = {
			"================================",
			"대원이 쓰러졌습니다.",
			"게임 오버.",
			"================================",
		};
		//std::cout << "\n================================" << '\n';
		//std::cout << "대원이 쓰러졌습니다." << '\n';
		//std::cout << "게임 오버." << '\n';
		//std::cout << "================================" << '\n';
	}
	g_cliRenderer.render(g_sceneData);

	currentStage.reset();
}

bool GameManager::isGameEnded() const
{
	return isGameOver;
}

void GameManager::resetGameState()
{
	isPlayerExit = true;
	isGameOver = false;
	battleCount = 1;
	currentStage.reset();
	clearMaps.clear();


	player = std::make_unique<Player>(createPlayer());
}

int GameManager::getBattleCount() const
{
	return battleCount;
}

void GameManager::increaseBattleCount()
{
	++battleCount;
}
