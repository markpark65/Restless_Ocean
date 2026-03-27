#include <iostream>

#include "Lobby.h"
#include "Player.h"
#include "GameManager.h"
#include "Dungeon.h"
#include "InputSystem.h"

void Lobby::start()
{
	//Player& player = GameManager::getInstance().getPlayer();

	
	std::cout << "\n로비로 왔습니다." << '\n';
}

void Lobby::update()
{
	std::cout << "안녕하세요. " << GameManager::getInstance().getPlayer().getName() << "님," << '\n';
	while (true)
	{
		std::cout << "무엇을 하시겠습니까?\n";
		std::cout << "1. 던전 입장\n";
		std::cout << "2. 상점 이용\n";
		std::cout << "3. 게임 종료\n";
	
		int input = InputSystem::getInputInt(1, 3);

		switch (input)
		{
		case 1:
			GameManager::getInstance().changeStage(std::make_unique<Dungeon>());
			return;
			break;
		case 2:
			GameManager::getInstance().changeStage(nullptr);
			return;
			break;
		case 3:
			GameManager::getInstance().changeStage(nullptr);
			std::cout << "게임을 종료합니다.\n";
			return;
			break;
		default:
			std::cout << "잘못된 입력입니다.\n";
			continue;
		}

	}
}

void Lobby::exit()
{
	std::cout << "로비를 떠납니다." << '\n';
}
