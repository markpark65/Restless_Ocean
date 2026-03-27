#include "Shop.h"
#include "Player.h"
#include <iostream>
using namespace std;

Shop::Shop() {

	items_.push_back(new HealthPotion("체력 포션", 100, 50));
	prices_.push_back(100);

	items_.push_back(new MaxHpUp("방수가 잘 되어있는 초코과자", 200, 10));
	prices_.push_back(200);

	items_.push_back(new OxygenPotion("산소 포션", 200, 10));
	prices_.push_back(200);

	items_.push_back(new MaxOxygenUp("1000년 전의 스노클", 200, 10));
	prices_.push_back(200);

	items_.push_back(new PressurePotion("압력 포션", 200, 10));
	prices_.push_back(200);

	items_.push_back(new MaxPressureUp("어느 물고기의 부례", 200, 10));
	prices_.push_back(200);

	items_.push_back(new AttackBoost("깨진 조개껍데기 목걸이", 200, 10));
	prices_.push_back(200);

}
Shop::~Shop() {
	for (auto item : items_) delete item;
}

void Shop::openShop(Player* player, Inventory<Item>& inventory) {
	int choice;

	while (true) {
		cout << "\n=== 상점 ===\n";
		cout << "1. 구매\n2. 판매\n0. 나가기\n";
		cin >> choice;

		if (choice == 1) buyItem(player, inventory);
		else if (choice == 2) sellItem(player, inventory);
		else break;
	}
}

void Shop::buyItem(Player* player, Inventory<Item>& inventory) {
	cout << "\n구매 목록:\n";
	for (int i = 0; i < items_.size(); i++) {
		cout << i << ": ";
		items_[i]->printInfo();
		cout << " 가격: " << prices_[i] << "G\n";
	}

	int choice;
	cin >> choice;

	if (choice < 0 || choice >= items_.size()) return;

	if (player->getGold() < prices_[choice]) {
		cout << "골드 부족!\n";
		return;
	}

	player->addGold(-prices_[choice]);

	inventory.addItem(items_[choice]->clone());

	cout << "구매 완료!\n 남은 골드 : "<<player->getGold()<<"\n";
}

void Shop::sellItem(Player* player, Inventory<Item>& inventory) {
	cout << "\n=== 판매 ===\n";
	inventory.printAll();

	int index;
	cin >> index;

	Item* item = inventory.getItem(index);
	if (!item) return;

	int sellPrice = static_cast<int>(item->getPrice() * 0.6);
	player->addGold(sellPrice);

	inventory.remove(index);

	cout << "판매 완료! +" << sellPrice << " G\n 남은 골드 : "<< player->getGold() << "\n";
}
