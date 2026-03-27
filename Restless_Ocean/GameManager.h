#pragma once

#include <iostream>

#include "Singleton.h"
#include "Player.h"

class Stage;

class GameManager : public Singleton<GameManager>
{
friend class Singleton<GameManager>;

private:
	Player			player;
	Stage*			currentStage;

public:
	Player& getPlayer();

	GameManager();

	std::string createPlayer();

	void changeStage(Stage* newStage);
	void run();
};

