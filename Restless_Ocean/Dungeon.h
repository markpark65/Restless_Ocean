#pragma once
#include "Stage.h"

class Dungeon : public Stage
{
	void start()	override;
	void update()	override;
	void exit()		override;
};

