#pragma once

#include "Stage.h"

class Lobby : public Stage
{
public:
	void start()	override;
	void update()	override;
	void exit()		override;
};

