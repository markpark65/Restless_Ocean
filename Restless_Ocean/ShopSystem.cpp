#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
using namespace std;
ShopSystem::ShopSystem() {
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 10, 50));
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 20, 10));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 30, 10));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 20, 10));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 10, 10));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 20, 10));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 20, 10));
}


void ShopSystem::buyItem(Player& player) {
	std::cout << "\n물품 목록:\n";
	for (size_t i = 0; i < items_.size(); i++) {
		std::cout << i << ": ";
		items_[i]->printInfo();
	}

	InputSystem inputSys;
	int index, quantity;

	std::cout << "구입 물품 번호";
	index = inputSys.getInputInt(0, static_cast<int>(items_.size() - 1));

	std::cout << "수량 ";
	quantity = inputSys.getInputInt(1, 99);

	int totalPrice = items_[index]->getPrice() * quantity;
	if (player.getGold() < items_[index]->getPrice()) {
		std::cout << "골드 부족!\n";
		return;
	}

	player.addGold(-totalPrice);
	for (int i = 0; i < quantity; i++) {
		player.getInventory().addItem(items_[index]->clone());
	};

	std::cout << "구매 완료! 남은 골드: " << player.getGold() << "\n";
}

void ShopSystem::sellItem(Player& player) {
	std::cout << "\n=== 판매 ===\n";
	player.getInventory().printAll();

	if (player.getInventory().getSize() == 0) {
		std::cout << "판매할 아이템이 없습니다.\n";
		return;
	}

	InputSystem inputSys;
	int index, quantity;

	std::cout << "판매할 아이템 번호";
	index = inputSys.getInputInt(0, player.getInventory().getSize() - 1);

	std::cout << "수량 ";
	quantity = inputSys.getInputInt(1, player.getInventory().getItemCount(index));
	Item* item = player.getInventory().getItem(index);

	int sellPrice = static_cast<int>(item->getPrice() * 0.6) * quantity;
	player.addGold(sellPrice);

	if (!item) {
		std::cout << "잘못된 선택입니다.\n";
		return;
	}
	player.getInventory().removeItem(index, quantity);

	std::cout << "판매 완료! +" << sellPrice << "G\n남은 골드: " << player.getGold() << "\n";
}
