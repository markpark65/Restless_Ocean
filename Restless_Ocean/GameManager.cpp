#include "GameManager.h"
#include "Player.h"
#include "MonsterFactory.h"
using namespace std;

//Monster* GameManager::generateMonster(int level) {
//	 
//}

void GameManager::battle(Player* player) {

	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster(player->getLevel());
	
	while (player->getHp() > 0 && monster->getHealth() > 0) {

		cout << "=============================" << endl;
		cout << "플레이어의 턴입니다!" << endl;
		// 플레이어의 공격
		cout << monster->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << endl;
		monster->takeDamage(player->getAttack());


		cout << "=============================" << endl;
		cout << "몬스터의 턴입니다!" << endl;
		// 몬스터의 공격
		cout << monster->getName() << "이(가) " << player->getName() << " 대원을 공격합니다!" << endl;
		player->takeDamage(monster->getAttack());
		

	}

	// 플레이어가 이겼을 때 보상 획득

	if (player->getHp() > 0) { //승리했을 때
		
		//보상 획득
		player->gainExp(50); 
		//if (player->getExp() > 100) {
		//	player->levelUp();
		//}

		// 골드 10~20 범위에서 랜덤 획득
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(10, 20);
		int gold = dis(gen);
		player->addGold(gold);

		//아이템 획득
	}

}

//void GameManager::displayInventory(Player* player) {
//
//}

void GameManager::startBattleSequence(Player* player) {



	battle(player);

	//상점 가는 기능
}