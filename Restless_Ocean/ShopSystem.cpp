#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
#include "Random.h"
using namespace std;
ShopSystem::ShopSystem() {

	//Level 1
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 10, 10,1));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 10, 10,1));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 10, 10,1));

	//Level 10
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 30, 10,10));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 30, 10,10));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 30, 10,10));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 30, 10,10));

	// Level 20
	items_.push_back(std::make_unique<WeaponUpgrade>("심해의 강화석", 100, 10, 20));
}

//구매
void ShopSystem::buyItem(Player& player) {
	std::cout << "\n물품 목록:\n";

	for (size_t i = 0; i < items_.size(); i++) {
		std::cout << i << ": ";
		items_[i]->printInfo();

		if (!items_[i]->isUnlocked(player.getLevel())) {
			std::cout << " [잠김]";
		}
		std::cout << "\n";
	}

	int gachaIndex = static_cast<int>(items_.size());
	std::cout << gachaIndex << ": [랜덤 아이템 뽑기 가격 : 5G]";
	if (player.getLevel() < 10) std::cout << " [잠김]";
	std::cout << "\n";

	InputSystem inputSys;
	int index;

	int maxIndex = gachaIndex;

	std::cout << "구입 물품 번호 ";
	index = inputSys.getInputInt(0, maxIndex);

	if (index == gachaIndex) {
		if (player.getLevel() < 10) {
			std::cout << "레벨 10 이상부터 이용 가능합니다!\n";
			return;
		}

		if (player.getGachaCount() >= MAX_GACHA) {
			std::cout << "가챠는 최대 10번까지만 가능합니다!\n";
			return;
		}

		int maxAvailable = MAX_GACHA - player.getGachaCount();

		std::cout << "뽑기 횟수 (최대 " << maxAvailable << "회) ";
		int count = inputSys.getInputInt(1, maxAvailable);

		for (int i = 0; i < count; i++) {

			if (player.getGold() < 5) {
				std::cout << "골드가 부족하여 중단됩니다.\n";
				break;
			}

			gacha(player);
			player.addGachaCount(1);
		}
		return;
	}

	if (!items_[index]->isUnlocked(player.getLevel())) {
		std::cout << "레벨 "
			<< items_[index]->getUnlockLevel()
			<< " 이상부터 이용 가능합니다!\n";
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


//판매 
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

//가챠
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

	std::cout << "[ 뽑기 진행 중... ]\n";
	int roll = Random::getRandomValue(0, 99);

	std::unique_ptr<Item> reward;

	if (roll < 50) {
		reward = std::make_unique<HealthPotion>("체력 포션", 10, 50, 1);
	}
	else if (roll < 80) {
		reward = std::make_unique<OxygenPotion>("산소 포션", 10, 10, 1);
	}
	else if (roll < 95) {
		reward = std::make_unique<PressurePotion>("압력 포션", 10, 10, 1);
	}
	else {
		reward = std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 30, 10, 10);
	}

	std::cout << "획득 아이템: ";
	reward->printInfo();
	std::cout << "\n";

	player.getInventory().addItem(reward.release());
}

//무기 강화
void ShopSystem::enhanceWeapon(Player& player) {
	InputSystem inputSys;

	std::cout << "\n=== 무기 강화 ===\n";

	std::vector<int> upgradeIndices;

	for (int i = 0; i < player.getInventory().getSize(); i++) {
		Item* item = player.getInventory().getItem(i);

		if (dynamic_cast<WeaponUpgrade*>(item)) {
			upgradeIndices.push_back(i);
			std::cout << upgradeIndices.size() - 1 << "번: ";
			item->printInfo();
			std::cout << "\n";
		}
	}

	if (upgradeIndices.empty()) {
		std::cout << "강화 아이템이 없습니다.\n";
		return;
	}

	std::cout << "사용할 아이템 번호 ";
	int choice = inputSys.getInputInt(0, upgradeIndices.size() - 1);

	int realIndex = upgradeIndices[choice];
	Item* item = player.getInventory().getItem(realIndex);

	item->use(&player);
	player.getInventory().removeItem(realIndex, 1);

	std::cout << "강화 완료!\n";
}


//공방 시스템
void ShopSystem::craftItem(Player& player) {
	InputSystem inputSys;

	std::cout << "\n=== 아이템 공방 ===\n";
	std::cout << "[합성 방법]\n";
	std::cout << "- 같은 아이템 2개 필요\n";
	std::cout << "- 체력 포션 → 강화 체력 포션\n";
	std::cout << "- 산소 포션 → 강화 산소 포션\n";
	std::cout << "- 압력 포션 → 강화 압력 포션\n\n";

	player.getInventory().printAll();

	if (player.getInventory().getSize() == 0) {
		std::cout << "아이템이 없습니다.\n";
		return;
	}
	std::cout << "합성할 아이템 번호 ";
	int index = inputSys.getInputInt(0, player.getInventory().getSize() - 1);

	Item* item = player.getInventory().getItem(index);

	if (!item) {
		std::cout << "잘못된 선택입니다.\n";
		return;
	}
	int count = player.getInventory().getItemCount(index);

	if (count < 2) {
		std::cout << "2개 이상 있어야 합성 가능합니다!\n";
		return;
	}
	int maxUsable = (count / 2) * 2;

	std::cout << "사용할 아이템 개수 (짝수, 최대 " << maxUsable << ") ";
	int useCount = inputSys.getInputInt(2, maxUsable);

	if (useCount % 2 != 0) {
		std::cout << "짝수 개수만 입력 가능합니다!\n";
		return;
	}

	int resultCount = useCount / 2;
	Item* newItem = nullptr;

	if (dynamic_cast<HealthPotion*>(item)) {
		newItem = new MegaHealthPotion();
	}
	else if (dynamic_cast<OxygenPotion*>(item)) {
		newItem = new MegaOxygenPotion();
	}
	else if (dynamic_cast<PressurePotion*>(item)) {
		newItem = new MegaPressurePotion();
	}
	else {
		std::cout << "이 아이템은 합성할 수 없습니다.\n";
		return;
	}

	player.getInventory().removeItem(index, useCount);

	for (int i = 0; i < resultCount; i++) {
		player.getInventory().addItem(newItem->clone());
	}

	delete newItem;

	std::cout << " 합성 성공! "
		<< resultCount << "개 생성되었습니다!\n";
}
