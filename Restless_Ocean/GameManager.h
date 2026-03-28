#pragma once

#include <iostream>

#include "Singleton.h"
#include "Player.h"
#include "Stage.h"

class GameManager : public Singleton<GameManager>
{
friend class Singleton<GameManager>;

private:
	Player					player;
	std::unique_ptr<Stage>	currentStage;
	bool					isGameOver = false;

public:
	Player& getPlayer();

	GameManager();

	std::string createPlayer();

	void changeStage(std::unique_ptr<Stage> newStage);
	void run();

	void endGame();
	bool isGameEnded() const;
};

