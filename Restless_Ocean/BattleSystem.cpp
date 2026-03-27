#include "BattleSystem.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "GameLogger.h"
#include "Random.h"
using namespace std;

GameLogger& logger = GameLogger::getInstance(); // 모든 출력 나중에 로거로 변경 예정
Random random;



void BattleSystem::battle(Player* player) {

	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster(player->getLevel());

	// 테스트용 Attack 수정
	//player->setAttack(10);


	// 전투 시작
	BattleResult battleResult = BattleResult::Continue;
	while (battleResult == BattleResult::Continue) {

		playerAction(player, monster, battleResult);

		if (battleResult != BattleResult::Continue) break;

		battleResult = checkBattleResult(player->getHp(), monster->getHealth());
		if (battleResult != BattleResult::Continue) break;

		monsterAction(player, monster);
		battleResult = checkBattleResult(player->getHp(), monster->getHealth());
	}

	// 전투 끝
	player->useOxygen(10);

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

	delete monster;

}

BattleResult BattleSystem::checkBattleResult(int playerHp, int monsterHp) {
	if (monsterHp <= 0) {
		return BattleResult::PlayerWin;
	}
	else if(playerHp <= 0) {
		return BattleResult::MonsterWin;
	}
	return BattleResult::Continue;
}

void BattleSystem::playerAction(Player* player, Monster* monster, BattleResult& battleResult) {
	cout << "=============================" << endl;
	cout << "플레이어의 턴입니다!" << endl;

	// 플레이어 행동 선택
	int choice;
	cout << "1. 공격한다" << '\n';
	cout << "2. 아이템을 사용한다" << '\n';
	cout << "3. 도망친다" << '\n';

	cout << "행동을 선택하세요: " << '\n';
	cin >> choice;




	switch (choice) {
	case 1:
		// 공격 로그 출력 ( 나중에 로그 로직으로 변경 예정 )
		cout << player->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << endl;
		monster->takeDamage(player->getAttack());
		break;
	case 2:
		// 아이템 사용
		cout << "아이템을 사용합니다." << '\n';
		// 아이템 사용 로직 추가 (예: 체력 회복, 공격력 증가 등)
		break;
	case 3:
		// 도망
		cout << "무사히 도망쳤습니다." << '\n';
		battleResult = BattleResult::RunAway;
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
