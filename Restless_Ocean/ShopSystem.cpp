#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
#include "Random.h"
using namespace std;
ShopSystem::ShopSystem() {

	//Level 1
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 10, 50, 0));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 10, 50, 0));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 10, 50, 0));

	//Level 5
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 30, 200, 5));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 30, 200, 5));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 30, 200, 5));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 30, 200, 5));

	// Level 10
	items_.push_back(std::make_unique<WeaponUpgrade>("심해의 강화석", 100, 20, 10));
}

//구매
void ShopSystem::buyItem(Player& player) {
	InputSystem inputSys;

	while (true) {

		std::cout << "\n=== 구매 ===\n";
		std::cout << "보유 골드 :" << player.getGold() << "G\n";
		std::cout << "0: [상점으로 돌아가기]\n\n";

		for (int i = 0; i < items_.size(); i++) {
			std::cout << i + 1 << ": ";
			items_[i]->printInfo();

			if (!items_[i]->isUnlocked(player.getLevel())) {
				std::cout << " [잠김]";
			}
			std::cout << "\n";
		}

		int gachaIndex = items_.size() + 1;
		std::cout << gachaIndex << ": [랜덤 아이템 뽑기 : 5G]";

		if (player.getLevel() < 10) {
			std::cout << " [잠김: 레벨 부족]";
		}
		else if (player.getGachaCount() >= MAX_GACHA) {
			std::cout << " [잠김: 횟수 초과]";
		}
		std::cout << "\n구매할 아이템 번호 ";

		int input = inputSys.getInputInt(0, gachaIndex);

		if (input == 0) return;

		if (input == gachaIndex) {

			if (player.getLevel() < 10) {
				std::cout << "레벨 부족!\n";
				continue;
			}

			if (player.getGachaCount() >= MAX_GACHA) {
				std::cout << "가챠 횟수 초과!\n";
				continue;
			}

			int remaining = MAX_GACHA - player.getGachaCount();
			std::cout << "뽑기 횟수 (최대 횟수 : " << remaining << ", 0:취소) ";

			int count = inputSys.getInputInt(0, remaining);

			if (count == 0) continue;

			for (int i = 0; i < count; i++) {
				if (player.getGold() < 5) {
					std::cout << "골드 부족!\n";
					break;
				}
				gacha(player);
				player.addGachaCount(1);
			}

			continue;
		}

		int index = input - 1;

		if (!items_[index]->isUnlocked(player.getLevel())) {
			std::cout << "레벨 부족!\n";
			continue;
		}

		std::cout << "수량 (0:취소) ";
		int quantity = inputSys.getInputInt(0, 99);

		if (quantity == 0) continue;

		int totalPrice = items_[index]->getPrice() * quantity;

		if (player.getGold() < totalPrice) {
			std::cout << "골드 부족!\n";
			continue;
		}

		player.addGold(-totalPrice);

		for (int i = 0; i < quantity; i++) {
			player.getInventory().addItem(items_[index]->clone());
		}

		std::cout << "구매 완료!\n";

	}
}


//판매 
void ShopSystem::sellItem(Player& player) {
	InputSystem inputSys;

	while (true) {
		std::cout << "\n=== 판매 ===\n";
		std::cout << "0: [상점으로 돌아가기]\n\n";
		int size = player.getInventory().getSize();

		if (player.getInventory().getSize() == 0) {
			std::cout << "판매할 아이템이 없습니다.\n";
			return;
		}

		player.getInventory().printAll();

		std::cout << "판매할 아이템 번호 ";
		int input = inputSys.getInputInt(0, player.getInventory().getSize());

		if (input == 0) return;

		int index = input - 1;

		Item* item = player.getInventory().getItem(index);

		std::cout << "수량 (0:취소) ";
		int quantity = inputSys.getInputInt(0, player.getInventory().getItemCount(index));

		if (quantity == 0) continue;

		int sellPrice = static_cast<int>(item->getPrice() * 0.6) * quantity;

		player.addGold(sellPrice);
		player.getInventory().removeItem(index, quantity);

		std::cout << "판매 완료! +" << sellPrice << "G\n";
	}
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

	while (true) {
		std::cout << "\n=== 무기 강화 ===\n";
		std::cout << "0: 상점으로 돌아가기\n\n";

		std::vector<int> upgradeIndices;

		for (int i = 0; i < player.getInventory().getSize(); i++) {
			Item* item = player.getInventory().getItem(i);

			if (dynamic_cast<WeaponUpgrade*>(item)) {
				upgradeIndices.push_back(i);

				std::cout << upgradeIndices.size() << ": ";
				item->printInfo();
				std::cout << " 수량: "
					<< player.getInventory().getItemCount(i)
					<< "\n";
			}
		}
		if (upgradeIndices.empty()) {
			std::cout << "강화 아이템이 없습니다.\n";
			return;
		}
		std::cout << "사용할 아이템 번호 선택 ";
		int input = inputSys.getInputInt(0, upgradeIndices.size());

		if (input == 0) return;

		int choice = input - 1;

		int realIndex = upgradeIndices[choice];
		Item* item = player.getInventory().getItem(realIndex);

		if (!item) {
			std::cout << "아이템 오류\n";
			continue;
		}
		/*if (!player.hasWeapon()) {
			std::cout << "장착된 무기가 없습니다!\n";
			continue;
		}*/
		item->use(&player);
		player.getInventory().removeItem(realIndex, 1);

		std::cout << "강화 완료!\n";
	}
}

//공방 시스템
void ShopSystem::craftItem(Player& player) {
	InputSystem inputSys;

	while (true) {
		std::cout << "\n=== 아이템 공방 ===\n";
		std::cout << "0: 상점으로 돌아가기\n\n";

		std::cout << "[합성 방법]\n";
		std::cout << "- 같은 아이템 2개 필요\n\n";

		player.getInventory().printAll();

		int size = player.getInventory().getSize();

		std::cout << "합성할 아이템 번호 선택 ";
		int input = inputSys.getInputInt(0, size);

		if (input == 0) return;

		int index = input - 1;

		Item* item = player.getInventory().getItem(index);

		if (!item) {
			std::cout << "아이템 오류\n";
			continue;
		}

		int count = player.getInventory().getItemCount(index);

		if (count < 2) {
			std::cout << "2개 이상 필요!\n";
			continue;
		}

		int maxUsable = (count / 2) * 2;

		std::cout << "사용 개수 (짝수, 0:취소): ";
		int useCount = inputSys.getInputInt(0, maxUsable);

		if (useCount == 0) continue;

		if (useCount % 2 != 0) {
			std::cout << "짝수만 가능!\n";
			continue;
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
			std::cout << "합성 불가 아이템!\n";
			continue;
		}

		player.getInventory().removeItem(index, useCount);

		for (int i = 0; i < resultCount; i++) {
			player.getInventory().addItem(newItem->clone());
		}

		delete newItem;

		std::cout << "합성 완료! " << resultCount << "개 생성!\n";
	}
}
