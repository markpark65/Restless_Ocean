#pragma once

#include <iostream>
#include <memory>

#include "Singleton.h"
#include "Player.h"
#include "Stage.h"
#include "DataType.h"

class IMap;

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

	std::vector<MapType>	clearMaps;

public:
	Player& getPlayer();
	std::string createPlayer();
	void resetBattleCount();

	GameManager();

	int getBattleCount() const;
	void increaseBattleCount();

	// 클리어 맵 보관
	bool hasClearMap(MapType map) const;			// 클리어한 맵인지 확인용
	void addClearMap(MapType map);					// 클리어 맵 추가
	std::unique_ptr<IMap> createNextMap() const;	// 맵 일단 순서대로

	// 플레이어가 게임 종료 버튼을 누르면 바로 종료
	void setIsPlayerExit(bool PlayerExit);

	void changeStage(std::unique_ptr<Stage> newStage);
	void run();

	void endGame(GameOverReason reason);
	bool isGameEnded() const;

	void resetGameState();
};

