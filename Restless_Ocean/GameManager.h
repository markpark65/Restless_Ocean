#pragma once

class Monster;
class Player;
class GameManager
{
	Monster* generateMonster(int level = 1);
	void battle(Player* player);
	void displayInventory(Player* player);
};

