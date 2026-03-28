#pragma once

#include <iostream>
#include <memory>

#include "Singleton.h"
#include "Player.h"
#include "Stage.h"

enum class GameOverReason
{
	Clear,
	Die,
};

class GameManager : public Singleton<GameManager>
{
friend class Singleton<GameManager>;

private:
	//Player					player;
	std::unique_ptr<Player> player;
	std::unique_ptr<Stage>	currentStage;
	int						battleCount = 1;
	bool					isPlayerExit = true;
	bool					isGameOver = false;

public:
	Player& getPlayer();
	std::string createPlayer();

	GameManager();

	int getBattleCount() const;
	void increaseBattleCount();

	// 플레이어가 게임 종료 버튼을 누르면 바로 종료
	void setIsPlayerExit(bool PlayerExit);

	void changeStage(std::unique_ptr<Stage> newStage);
	void run();

	void endGame(GameOverReason reason);
	bool isGameEnded() const;

	void resetGameState();
};

