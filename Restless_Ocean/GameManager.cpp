#include "GameManager.h"
#include "Stage.h"
#include "Lobby.h"
#include "InputSystem.h"

Player& GameManager::getPlayer()
{
	return player;
}

GameManager::GameManager()
	: player(createPlayer())
{ }

std::string GameManager::createPlayer()
{
	std::cout << "생성할 캐릭터의 이름을 입력하세요." << '\n';

	std::string name = InputSystem::getInputStr();
	return name;
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
	GameManager::getInstance().changeStage(std::make_unique<Lobby>());

	while (currentStage)
	{
		currentStage->update();
	}
}
