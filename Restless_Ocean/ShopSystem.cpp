#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
using namespace std;
ShopSystem::ShopSystem() {
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 100, 50));
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 200, 10));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 200, 10));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 200, 10));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 200, 10));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 200, 10));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 200, 10));
}

void ShopSystem::openShop(Player& player, Inventory<Item>& inventory) {
	InputSystem inputSys;
	int choice;

	while (true) {
		std::cout << "\n=== 상점 ===\n";
		std::cout << "1. 구매\n2. 판매\n0. 나가기\n";
		choice = inputSys.getInputInt(0, 2);

		if (choice == 1) buyItem(player, inventory);
		else if (choice == 2) sellItem(player, inventory);
		else break;
	}
}

void ShopSystem::buyItem(Player& player, Inventory<Item>& inventory) {
	std::cout << "\n구매 목록:\n";
	for (size_t i = 0; i < items_.size(); i++) {
		std::cout << i << ": ";
		items_[i]->printInfo();
		std::cout << " 가격: " << items_[i]->getPrice() << "G\n";
	}

	InputSystem inputSys;
	int choice = inputSys.getInputInt(0, static_cast<int>(items_.size() - 1));

	if (player.getGold() < items_[choice]->getPrice()) {
		std::cout << "골드 부족!\n";
		return;
	}

	player.addGold(-items_[choice]->getPrice());
	inventory.addItem(items_[choice]->clone());

	std::cout << "구매 완료! 남은 골드: " << player.getGold() << "\n";
}

void ShopSystem::sellItem(Player& player, Inventory<Item>& inventory) {
	std::cout << "\n=== 판매 ===\n";
	inventory.printAll();

	if (inventory.getSize() == 0) {
		std::cout << "판매할 아이템이 없습니다.\n";
		return;
	}

	InputSystem inputSys;
	int index = inputSys.getInputInt(0, inventory.getSize() - 1);

	Item* item = inventory.getItem(index);
	if (!item) {
		std::cout << "잘못된 선택입니다.\n";
		return;
	}

	int sellPrice = static_cast<int>(item->getPrice() * 0.6);
	player.addGold(sellPrice);
	inventory.remove(index);

	std::cout << "판매 완료! +" << sellPrice << "G\n남은 골드: " << player.getGold() << "\n";
}
