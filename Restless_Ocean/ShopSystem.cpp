#include "ShopSystem.h"
#include "Player.h"
#include "InputSystem.h"
#include <iostream>
#include "Random.h"
#include "GlobalVal.h"
using namespace std;
ShopSystem::ShopSystem() {

	//Level 1
	items_.push_back(std::make_unique<HealthPotion>("체력 포션", 10, 50,0));
	items_.push_back(std::make_unique<OxygenPotion>("산소 포션", 10, 50,0));
	items_.push_back(std::make_unique<PressurePotion>("압력 포션", 10, 50,0));

	//Level 10
	items_.push_back(std::make_unique<MaxHpUp>("방수가 잘 되어있는 초코과자", 30, 200,10));
	items_.push_back(std::make_unique<MaxOxygenUp>("1000년 전의 스노클", 30, 200,10));
	items_.push_back(std::make_unique<MaxPressureUp>("어느 물고기의 부례", 30, 200,10));
	items_.push_back(std::make_unique<AttackBoost>("깨진 조개껍데기 목걸이", 30, 200,10));

	// Level 20
	items_.push_back(std::make_unique<WeaponUpgrade>("심해의 강화석", 100, 100, 20));
}

//구매
void ShopSystem::buyItem(Player& player) {
	InputSystem inputSys;

	while (true) { 
		g_sceneData.sceneText = {};
		g_sceneData.sceneText.push_back("=== 구매 === ");
		g_sceneData.sceneText.push_back("보유 골드 :" + std::to_string(player.getGold())+ "G");
		g_sceneData.options = { "상점으로 돌아가기" };
		g_sceneData.sceneText.push_back("0: [상점으로 돌아가기]");
		//std::cout << "\n=== 구매 ===\n";
		//std::cout << "보유 골드 :" << player.getGold()<<"G\n";
		//std::cout << "0: [상점으로 돌아가기]\n\n";

		for (int i = 0; i < items_.size(); i++) {
			std::string str = std::to_string(i + 1)+ ": " + items_[i]->tostring();
			//std::cout << i + 1 << ": ";
			//items_[i]->printInfo();

			if (!items_[i]->isUnlocked(player.getLevel())) {
				//std::cout << " [잠김]";
				str += " [잠김]";
			}
			else {
				std::string name = items_[i]->getName();

				//이름이너무길어
				if (name == "방수가 잘 되어있는 초코과자")
					name = "초코과자";
				g_sceneData.options.push_back(name);
			}

			g_sceneData.sceneText.push_back(str);
			//std::cout << "\n";
		}

		int gachaIndex = items_.size() + 1;
		//std::cout << gachaIndex << ": [랜덤 아이템 뽑기 : 5G]";
		std::string gachaStr = std::to_string(gachaIndex) + ": [랜덤 아이템 뽑기 : 5G]";
		if (player.getLevel() < 10) {
			gachaStr += " [잠김: 레벨 부족]";
			//std::cout << " [잠김: 레벨 부족]";
		}
		else if (player.getGachaCount() >= MAX_GACHA) {
			gachaStr += " [잠김: 횟수 초과]";
			//std::cout << " [잠김: 횟수 초과]";
		}
		else {
			g_sceneData.options.push_back("랜덤 아이템 뽑기");
		}
		g_sceneData.sceneText.push_back(gachaStr);
		//std::cout << "\n구매할 아이템 번호 ";
		g_cliRenderer.render(g_sceneData);
		int input = g_cliRenderer.OptionSelector(g_sceneData);
		//int input = inputSys.getInputInt(0, gachaIndex);

		if (input == 0) {
			g_sceneData.description = "상점으로 복귀합니다.";
			return;
		}

		if (input == gachaIndex) {

			if (player.getLevel() < 10) {
				g_sceneData.description = "레벨 부족 \n ";
				//std::cout << "레벨 부족!\n";
				continue; 
			}

			if (player.getGachaCount() >= MAX_GACHA) {
				g_sceneData.description = "가챠 횟수 초과! \n ";
				//std::cout << "가챠 횟수 초과!\n";
				continue;
			}

			int remaining = MAX_GACHA - player.getGachaCount();
			//std::cout << "뽑기 횟수 (최대 횟수 : " << remaining << ", 0:취소) ";

			int count = 1;//inputSys.getInputInt(0, remaining);

			if (count == 0) continue; 

			for (int i = 0; i < count; i++) {
				if (player.getGold() < 5) {
					g_sceneData.description = "골드 부족! \n ";
					//std::cout << "골드 부족!\n";
					break;
				}
				gacha(player);
				player.addGachaCount(1);
			}

			continue;
		}

		int index = input - 1;

		if (!items_[index]->isUnlocked(player.getLevel())) {
			g_sceneData.description = "레벨 부족! \n ";
			//std::cout << "레벨 부족!\n";
			continue;
		}

		//std::cout << "수량 (0:취소) ";
		int quantity = 1;// inputSys.getInputInt(0, 99);

		if (quantity == 0) continue;

		int totalPrice = items_[index]->getPrice() * quantity;

		if (player.getGold() < totalPrice) {
			g_sceneData.description = "골드 부족! \n ";
			//std::cout << "골드 부족!\n";
			continue;
		}

		player.addGold(-totalPrice);

		for (int i = 0; i < quantity; i++) {
			player.getInventory().addItem(items_[index]->clone());
		}

		g_sceneData.description = "구매 완료! \n ";
		//std::cout << "구매 완료!\n";

	}
}


//판매 
void ShopSystem::sellItem(Player& player) {
	InputSystem inputSys;

	g_sceneData.selectedIndex = 0;
	while (true) {
		g_sceneData.sceneText = {};
		g_sceneData.sceneText.push_back("=== 판매 === ");
		g_sceneData.sceneText.push_back("0: [상점으로 돌아가기]");
		g_sceneData.options = { "상점으로 돌아가기" };
		//std::cout << "\n=== 판매 ===\n";
		//std::cout << "0: [상점으로 돌아가기]\n\n";
		int size = player.getInventory().getSize();

		if (player.getInventory().getSize() == 0) {
			g_sceneData.description += "더 판매할 아이템이 없습니다. \n ";
			//std::cout << "판매할 아이템이 없습니다.\n";
			return;
		}
		
		std::vector<std::string> items = player.getInventory().printAllstr();
		for (auto& it : items) {
			g_sceneData.sceneText.push_back(it);
			//g_sceneData.options.push_back(it);
		}
		for (int i = 0; i < player.getInventory().getSize(); i++) {
			Item* item = player.getInventory().getItem(i);
			//g_sceneData.sceneText.push_back(item->tostring());
			std::string name = item->getName();

			//이름이너무길어
			if (name == "방수가 잘 되어있는 초코과자")
				name = "초코과자";
			g_sceneData.options.push_back(name);

		}
		g_cliRenderer.render(g_sceneData);
		//std::cout << "판매할 아이템 번호 ";
		int input = g_cliRenderer.OptionSelector(g_sceneData);
		//int input = inputSys.getInputInt(0, player.getInventory().getSize());

		if (input == 0) {
			g_sceneData.description = "상점으로 복귀합니다.";
			return;
		}

		int index = input - 1;

		Item* item = player.getInventory().getItem(index);

		//std::cout << "수량 (0:취소) ";
		int quantity = 1;// inputSys.getInputInt(0, player.getInventory().getItemCount(index));

		if (quantity == 0) continue;

		int sellPrice = static_cast<int>(item->getPrice() * 0.6) * quantity;

		player.addGold(sellPrice);
		player.getInventory().removeItem(index, quantity);

		g_sceneData.description = "판매 완료! \n ";
		//std::cout << "판매 완료! +" << sellPrice << "G\n";
	}
}

//가챠
void ShopSystem::gacha(Player& player) {
	const int cost = 5;

	if (player.getLevel() < 10) {
		g_sceneData.description = "레벨 10 이상부터 이용 가능합니다! \n ";
		std::cout << "레벨 10 이상부터 이용 가능합니다!\n";
		return;
	}

	if (player.getGold() < cost) {
		g_sceneData.description = "골드가 부족합니다! \n ";
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

	g_sceneData.description = reward->getName() + "획득! \n ";
	//std::cout << "획득 아이템: ";
	reward->printInfo();
	//std::cout << "\n";

	player.getInventory().addItem(reward.release());
}


//무기 강화
void ShopSystem::enhanceWeapon(Player& player) {
	InputSystem inputSys;

	while (true) {
		g_sceneData.sceneText = {};
		g_sceneData.sceneText.push_back("=== 무기 강화 === ");
		g_sceneData.sceneText.push_back("0: [상점으로 돌아가기]");
		g_sceneData.sceneText.push_back("1: [무기 강화하기]");
		g_sceneData.selectedIndex = 0;
		g_sceneData.options = { "상점으로 돌아가기", "무기 강화하기"};
		g_cliRenderer.render(g_sceneData);

		//std::cout << "\n=== 무기 강화 ===\n";
		//std::cout << "0: 상점으로 돌아가기\n\n";

		std::vector<int> upgradeIndices;

		for (int i = 0; i < player.getInventory().getSize(); i++) {
			Item* item = player.getInventory().getItem(i);

			if (dynamic_cast<WeaponUpgrade*>(item)) {
				upgradeIndices.push_back(i);
				std::string str = "";
				str += std::to_string(upgradeIndices.size()) + ": ";
				//std::cout << upgradeIndices.size() << ": ";
				str += item->tostring();
				//item->printInfo();
				str += " 수량: " + std::to_string(player.getInventory().getItemCount(i)) + " \n ";
				g_sceneData.description += str;
				//std::cout << " 수량: " << player.getInventory().getItemCount(i) << "\n";

				//std::string str = std::to_string(i + 1) + ": " + items_[i]->getName() + ", 가격" + std::to_string(items_[i]->getPrice()) + "G, 필요 레벨 : " + std::to_string(items_[i]->getUnlockLevel());
			}
		}
		if (upgradeIndices.empty()) {
			g_sceneData.description = "강화 아이템이 없습니다. \n ";
			//std::cout << "강화 아이템이 없습니다.\n";
			return;
		}
		g_sceneData.description += "강화하시겟습니까? \n ";
		//std::cout << "사용할 아이템 번호 선택 ";
		int input = g_cliRenderer.OptionSelector(g_sceneData);
		//inputSys.getInputInt(0, upgradeIndices.size());

		if (input == 0) {
			g_sceneData.description = "상점으로 복귀합니다.";
			return;
		}

		int choice = input - 1;
		
		int realIndex = upgradeIndices[choice];
		Item* item = player.getInventory().getItem(realIndex);

		if (!item) {
			g_sceneData.description += "아이템 오류 \n ";
			//std::cout << "아이템 오류\n";
			continue;
		}
		if (!player.hasWeapon()) {
			g_sceneData.description = "장착된 무기가 없습니다!(던전 입장시 무기 장착) \n ";
			g_sceneData.description += "상점으로 돌아갑니다. \n ";
			//std::cout << "장착된 무기가 없습니다!\n";
			return;
			continue;
		}
		item->use(&player);
		player.getInventory().removeItem(realIndex, 1);

		g_sceneData.description += "강화 완료! \n ";
		//std::cout << "강화 완료!\n";
	}
}

//공방 시스템
void ShopSystem::craftItem(Player& player) {
	InputSystem inputSys;

	g_sceneData.description = "합성할 아이템 선택 \n ";
	g_sceneData.description = "[합성 방법] \n ";
	g_sceneData.description += "- 같은 아이템 2개 필요 \n ";
	g_sceneData.selectedIndex = 0;
	while (true) {
		g_sceneData.sceneText = {};
		g_sceneData.sceneText.push_back("=== 아이템 공방 === ");
		g_sceneData.sceneText.push_back("0: [상점으로 돌아가기]");
		g_sceneData.options = { "상점으로 돌아가기"};

		//std::cout << "\n=== 아이템 공방 ===\n";
		//std::cout << "0: 상점으로 돌아가기\n\n";
		//std::cout << "[합성 방법]\n";
		//std::cout << "- 같은 아이템 2개 필요\n\n";

		//player.getInventory().printAll();
		std::vector<std::string> items = player.getInventory().printAllstr();
		for (auto& it : items) {
			g_sceneData.sceneText.push_back(it);
			//g_sceneData.options.push_back(it);
		}
		for (int i = 0; i < player.getInventory().getSize(); i++) {
			Item* item = player.getInventory().getItem(i);
			//g_sceneData.sceneText.push_back(item->tostring());
			std::string name = item->getName();

			//이름이너무길어
			if (name == "방수가 잘 되어있는 초코과자")
				name = "초코과자";
			g_sceneData.options.push_back(name);

		}
		//int size = player.getInventory().getSize();

		//std::cout << "합성할 아이템 번호 선택 ";
		//int input = inputSys.getInputInt(0, size);

		int input = g_cliRenderer.OptionSelector(g_sceneData);
		g_sceneData.description = "[합성 방법] \n ";
		g_sceneData.description += "- 같은 아이템 2개 필요 \n ";
		if (input == 0) {
			g_sceneData.description = "상점으로 복귀합니다.";
			return;
		}

		int index = input - 1;

		Item* item = player.getInventory().getItem(index);

		if (!item) {
			g_sceneData.description += "아이템 오류 \n ";
			std::cout << "아이템 오류\n";
			continue;
		}

		int count = player.getInventory().getItemCount(index);

		if (count < 2) {
			g_sceneData.description += "2개 이상 필요! \n ";
			std::cout << "2개 이상 필요!\n";
			continue;
		}

		//int maxUsable = (count / 2) * 2;

		//std::cout << "사용 개수 (짝수, 0:취소): ";
		//int useCount = inputSys.getInputInt(0, maxUsable);
		int useCount = 2;
		if (useCount == 0) continue;

		if (useCount % 2 != 0) {
			//std::cout << "짝수만 가능!\n";
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
			g_sceneData.description += "합성 불가 아이템! \n ";
			//std::cout << "합성 불가 아이템!\n";
			continue;
		}

		player.getInventory().removeItem(index, useCount);

		for (int i = 0; i < resultCount; i++) {
			player.getInventory().addItem(newItem->clone());
		}
		std::string itemName = newItem->getName();
		delete newItem;

		g_sceneData.description += "합성 완료! " + itemName + std::to_string(resultCount) + "개 생성! \n ";
		g_cliRenderer.render(g_sceneData);
		//std::cout << "합성 완료! " << resultCount << "개 생성!\n";
	}
}
