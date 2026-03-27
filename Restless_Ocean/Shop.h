#pragma once
#include "Stage.h"
#include "ShopSystem.h"

class Shop : public Stage
{
private:
	ShopSystem shopSystem;

public:
	void start()	override;
	void update()	override;
	void exit()		override;
};

