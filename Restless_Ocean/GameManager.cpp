#include "GameManager.h"
#include "Player.h"
#include "MonsterFactory.h"
using namespace std;

//Monster* GameManager::generateMonster(int level) {
//	 
//}

void GameManager::battle(Player* player) {

	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster();

	while (player->getHp() > 0 && monster->getHealth() > 0) {

		// ---플레이어의 턴---
		cout << "=============================" << endl;
		cout << "플레이어의 턴입니다!" << endl;
		// 플레이어의 공격
		cout << monster->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << endl;
		monster->takeDamage(player->getAttack());

		// ---몬스터의 턴---
		cout << "=============================" << endl;
		cout << "몬스터의 턴입니다!" << endl;
		// 몬스터의 공격
		cout << monster->getName() << "이(가) " << player->getName() << " 대원을 공격합니다!" << endl;
		player->takeDamage(monster->getAttack());

		
	}
	

}

//void GameManager::displayInventory(Player* player) {
//
//}

void GameManager::startBattleSequence(Player* player) {
	
}