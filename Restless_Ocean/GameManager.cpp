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

	while (currentStage && !isGameOver)
	{
		currentStage->update();
	}
}

void GameManager::endGame()
{
	isGameOver = true;

	std::cout << "\n================================" << '\n';
	std::cout << "모든 유적을 모았습니다!" << '\n';
	std::cout << "심해의 비밀이 드러납니다." << '\n';
	std::cout << "(대충 왕국과 심해어들의 비밀)" << '\n';
	std::cout << "게임을 종료합니다." << '\n';
	std::cout << "================================" << '\n';

	currentStage.reset();
}

bool GameManager::isGameEnded() const
{
	return isGameOver;
}
