#pragma once

#include <iostream>

#include "Singleton.h"
#include "Player.h"

class Stage;

class Manager : public Singleton<Manager>
{
friend class Singleton<Manager>;

private:
	Player			player;
	//CurretStage		currentStage;
	Stage* currentStage;

public:
	Player& getPlayer();

	Manager() : player(createPlayer()) {}

	std::string createPlayer()
	{
		std::cout << "이름을 입력하세요." << '\n';
		std::cout << "> ";
		std::string name;
		std::cin >> name;

		return name;
	}

	void changeStage(Stage* newStage);
	void run();
};

