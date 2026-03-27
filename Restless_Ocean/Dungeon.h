#pragma once
#include "Stage.h"
#include "BattleSystem.h"

class Dungeon : public Stage
{
private:
	BattleSystem battleSystem;

public:
	void start()	override;
	void update()	override;
	void exit()		override;
};

