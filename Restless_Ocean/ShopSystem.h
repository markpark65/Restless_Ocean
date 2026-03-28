#pragma once
#include <vector>
#include "Item.h"
#include "Inventory.h"

class Player;

class Player;

class ShopSystem {
public:
	ShopSystem();
	~ShopSystem() = default;

private:
	std::vector<std::unique_ptr<Item>> items_; 
	const int MAX_GACHA = 10;

public:
	void buyItem(Player& player);
	void sellItem(Player& player);
	void gacha(Player& player);
	void enhanceWeapon(Player& player);
	void craftItem(Player& player);
};
