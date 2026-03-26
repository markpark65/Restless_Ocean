#pragma once

class Monster;
class Player;
class GameManager
{
public:
	void battle(Player* player);
	//void displayInventory(Player* player);

	void startBattleSequence(Player* player);
};

