#pragma once

class Monster;
class Player;
class BattleSystem
{
public:
	void battle(Player* player);
	//void displayInventory(Player* player);

	void startBattleSequence(Player* player);

	void playerAction(Player* player, Monster* monster);
	void monsterAction(Player* player, Monster* monster);
};

