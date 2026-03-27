#pragma once
#include <vector>
#include "Item.h"
#include "Inventory.h"

class Player;

class Shop {
public:
	Shop();
	~Shop();
	void openShop(Player* player, Inventory<Item>& inventory);

private:
	std::vector<Item*> items_;
	std::vector<int> prices_;

	void buyItem(Player* player, Inventory<Item>& inventory);
	void sellItem(Player* player, Inventory<Item>& inventory);
};
