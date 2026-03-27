#include <iostream>
#include "Player.h"
#include "Inventory.h"
#include "Shop.h"
#include "Item.h"

using namespace std;

int main() {
	// 1️⃣ 플레이어 생성
	Player player("심해탐사대원");

	// 2️⃣ 플레이어 인벤토리 생성 (최대 10칸)
	Inventory<Item> playerInventory(10);

	// 3️⃣ 상점 생성
	Shop shop;

	int action = -1;
	while (true) {
		cout << "\n========================\n";
		cout << "1. 상점 입장\n";
		cout << "2. 인벤토리 확인\n";
		cout << "3. 상태 확인\n";
		cout << "0. 종료\n";
		cout << "선택: ";
		cin >> action;

		if (action == 1) {
			shop.openShop(&player, playerInventory);
		}
		else if (action == 2) {
			cout << "\n=== 플레이어 인벤토리 ===\n";
			playerInventory.printAll();
		}
		else if (action == 3) {
			player.showStatus();
		}
		else if (action == 0) {
			cout << "게임 종료\n";
			break;
		}
		else {
			cout << "잘못된 선택입니다.\n";
		}
	}

	return 0;
}
