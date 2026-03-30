#pragma once
#include "Stage.h"
#include "BattleSystem.h"
#include "WeaponManager.h"
#include "IMap.h"
#include <memory>

class Dungeon : public Stage
{
private:
	BattleSystem battleSystem;
	WeaponManager weaponManager;
	std::unique_ptr<IMap> currentMap;

public:
	Dungeon();
	Dungeon(std::unique_ptr<IMap> map);
	void start()	override;
	void update()	override;
	void exit()		override;
};

