#include "BattleSystem.h"
#include "Player.h"
#include "MonsterFactory.h"
using namespace std;

void BattleSystem::battle(Player* player) {

	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster(player->getLevel());
	
	while (player->getHp() > 0 && monster->getHealth() > 0) {

		playerAction(player, monster);
		monsterAction(player, monster);

	}

	// 플레이어가 이겼을 때 보상 획득

	if (player->getHp() > 0) { //승리했을 때
		
		//보상 획득
		player->gainExp(50); 

		// 골드 10~20 범위에서 랜덤 획득
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(10, 20);
		int gold = dis(gen);
		player->addGold(gold);

		//아이템 획득
	}

}


void BattleSystem::playerAction(Player* player, Monster* monster) {
	cout << "=============================" << endl;
	cout << "플레이어의 턴입니다!" << endl;

	// 플레이어 행동 선택
	int choice;
	cout << "1. 공격한다" << endl;
	cout << "2. 아이템을 사용한다" << endl;
	cout << "3. 도망친다" << endl;

	cout << "행동을 선택하세요: " << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		// 공격 로그 출력 ( 나중에 로그 로직으로 변경 예정 )
		cout << player->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << endl;
		monster->takeDamage(player->getAttack());
		break;
	case 2:
		// 아이템 사용
		break;
	case 3:
		// 도망
		cout << "무사히 도망쳤습니다." << endl;
		break;
	default:
		break;
	}

}

void BattleSystem::monsterAction(Player* player, Monster* monster) {

	cout << "=============================" << endl;
	cout << "몬스터의 턴입니다!" << endl;
	// 몬스터의 공격
	cout << monster->getName() << "이(가) " << player->getName() << " 대원을 공격합니다!" << endl;
	player->takeDamage(monster->getAttack());


}

void BattleSystem::startBattleSequence(Player* player) {

	battle(player);

	//상점 가는 기능
}
