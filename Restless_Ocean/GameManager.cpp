#include "GameManager.h"
#include "Player.h"
#include "MonsterFactory.h"


//Monster* GameManager::generateMonster(int level) {
//	 
//}

void GameManager::battle(Player* player) {
	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster();

	while (player->getHp() > 0 && monster->getHealth() > 0) {

		// 몬스터의 공격
		player->takeDamage(monster->getAttack());

		// 플레이어의 공격
		monster->takeDamage(player->getAttack());
	}
	
}

//void GameManager::displayInventory(Player* player) {
//
//}