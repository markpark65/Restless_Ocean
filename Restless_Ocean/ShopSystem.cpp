#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
#include "Random.h"
using namespace std;
ShopSystem::ShopSystem() {

	//Level 1
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 10, 50,1));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 10, 10,1));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 10, 10,1));

	//Level 10
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 30, 10,10));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 30, 10,10));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 30, 10,10));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 30, 10,10));
}


void ShopSystem::buyItem(Player& player) {
	std::cout << "\n물품 목록:\n";
	int unlockedCount = -1; 

	
	for (size_t i = 0; i < items_.size(); i++) {
		std::cout << i << ": ";
		items_[i]->printInfo();

		if (!items_[i]->isUnlocked(player.getLevel())) {
			std::cout << " [잠김]";
		}
		else {
			unlockedCount = static_cast<int>(i); 
		}
		std::cout << "\n";
	}

	
	int gachaIndex = static_cast<int>(items_.size());
	std::cout << gachaIndex << ": [ 랜덤 아이템 뽑기 가격 : 5G ]";
	if (player.getLevel() < 10) std::cout << " [잠김]";
	std::cout << "\n";

	InputSystem inputSys;
	int index;


	int maxIndex = unlockedCount;
	if (player.getLevel() >= 10) maxIndex = gachaIndex; 

	std::cout << "구입 물품 번호";
	index = inputSys.getInputInt(0, maxIndex);

	
	if (index == gachaIndex) {
		gacha(player);
		return;
	}
	
	if (!items_[index]->isUnlocked(player.getLevel())) {
		std::cout << "이 아이템은 아직 구매할 수 없습니다!\n";
		return;
	}

	std::cout << "수량 ";
	int quantity = inputSys.getInputInt(1, 99);

	
	int totalPrice = items_[index]->getPrice() * quantity;
	if (player.getGold() < totalPrice) {
		std::cout << "골드 부족!\n";
		return;
	}

	player.addGold(-totalPrice);
	for (int i = 0; i < quantity; i++) {
		player.getInventory().addItem(items_[index]->clone());
	}

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

void ShopSystem::gacha(Player& player) {
	const int cost = 5;

	if (player.getLevel() < 10) {
		std::cout << "레벨 10 이상부터 이용 가능합니다!\n";
		return;
	}

	if (player.getGold() < cost) {
		std::cout << "골드가 부족합니다!\n";
		return;
	}

	player.addGold(-cost);

	std::cout << "\n 뽑기 진행 중...\n";
	int roll = Random::getRandomValue(0, 99);

	Item* reward = nullptr;

	if (roll < 50) {
		reward = new HealthPotion("체력 포션", 10, 50, 1);
	}
	else if (roll < 80) {
		reward = new OxygenPotion("산소 포션", 10, 10, 1);
	}
	else if (roll < 95) {
		reward = new PressurePotion("압력 포션", 10, 10, 1);
	}
	else {
		reward = new AttackBoost("깨진 조개껍데기 목걸이", 30, 10, 10);
	}

	std::cout << "획득 아이템: ";
	reward->printInfo();
	std::cout << "\n";

	player.getInventory().addItem(reward);
}

