#include <iostream>

#include "Lobby.h"
#include "Player.h"
#include "Manager.h"
#include "Dungeon.h"

void Lobby::start()
{
	//Player& player = Manager::getInstance().getPlayer();

	
	std::cout << "\n로비로 왔습니다." << '\n';
}

void Lobby::update()
{
	while (true)
	{
		std::cout << "\n안녕하세요. " << Manager::getInstance().getPlayer().getName() << "님," << '\n';
		std::cout << "무엇을 하시겠습니까?\n";
		std::cout << "1. 던전 입장\n";
		std::cout << "2. 상점 이용\n";
		std::cout << "3. 게임 종료\n";
		std::cout << "> ";
	
		int input = 0;
		std::cin >> input;

		switch (input)
		{
		case 1:
			Manager::getInstance().changeStage(new Dungeon);
			return;
			break;
		case 2:
			Manager::getInstance().changeStage(nullptr);
			return;
			break;
		case 3:
			Manager::getInstance().changeStage(nullptr);
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