#pragma once
#include "Stage.h"
//#include "IMap.h" //map class
//#include "MapType.h" //enum class

class Dungeon : public Stage
{
public:
	void start()	override;
	void update()	override;
	void exit()		override;
//private:
//	void selectRandomMap();
//	std::unique_ptr<IMap> currentMap_; //map class
//private:
//	void selectRandomMap();
//	MapType currentMapType_; //enum class
};

