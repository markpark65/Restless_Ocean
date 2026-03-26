#include "Manager.h"
#include "Stage.h"
#include "Lobby.h"

Player& Manager::getPlayer()
{
	return player;
}

void Manager::changeStage(Stage* newStage)
{
	if (currentStage != nullptr)
	{
		currentStage->exit();
	}

	currentStage = newStage;

	if (currentStage != nullptr)
	{
		currentStage->start();
	}
}

void Manager::run()
{
	currentStage = new Lobby;

	while (currentStage)
	{
		currentStage->update();
	}
}