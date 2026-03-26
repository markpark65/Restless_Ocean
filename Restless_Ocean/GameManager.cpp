#include "GameManager.h"
#include "Player.h"

//구현 전

//Monster* GameManager::generateMonster(int level) {}
void GameManager::battle(Player* player) {
	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster();

	while (player->getHp() > 0 && monster->getHealth() > 0) {
	
	}
}
//void GameManager::displayInventory(Player* player) {
//
//}