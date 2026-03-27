#pragma once
#include <vector>
#include "Item.h"
#include "Inventory.h"

class Player;

class Player;

class Shop {
public:
	Shop();
	~Shop() = default;

	void openShop(Player* player, Inventory<Item>& inventory);

private:
	std::vector<std::unique_ptr<Item>> items_;

	void buyItem(Player* player, Inventory<Item>& inventory);
	void sellItem(Player* player, Inventory<Item>& inventory);
};
