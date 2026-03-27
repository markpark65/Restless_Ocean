#include "BattleSystem.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "GameLogger.h"
#include "Random.h"
#include "InputSystem.h"
using namespace std;

GameLogger& logger = GameLogger::getInstance(); // 모든 출력 나중에 로거로 변경 예정
Random random;



BattleResult BattleSystem::battle(Player* player) {

	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster(player->getLevel());

	// 전투 시작
	BattleResult battleResult = BattleResult::Continue;
	while (battleResult == BattleResult::Continue) {

		if (player->getSpeed() >= monster->getSpeed()) {
			// 플레이어가 먼저 행동
			playerAction(player, monster, battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleResult(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;
			monsterAction(player, monster);
			battleResult = checkBattleResult(player->getHp(), monster->getHealth());
		}
		else {
			// 몬스터가 먼저 행동
			monsterAction(player, monster);
			battleResult = checkBattleResult(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			playerAction(player, monster, battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleResult(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

		}
		
	}

	delete monster;
	return battleResult;
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
	cout << "*" << '\n';
	cout << "플레이어의 턴입니다!" << '\n';

	// 플레이어 행동 선택
	int choice = 0;
	cout << "1. 일반 공격" << '\n';
	cout << "2. 스킬 사용" << '\n';
	cout << "3. 아이템 사용" << '\n';
	cout << "4. 도망치기" << '\n';


	InputSystem inputSystem;
	cout << "행동을 선택하세요: " << '\n';
	choice = inputSystem.getInputInt(1, 4);

	switch (choice) {
	case 1:
		// 공격 로그 출력 ( 나중에 로그 로직으로 변경 예정 )
		cout << player->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << '\n';
		monster->takeDamage(player->getAttack());
		break;
	case 2:
		// 스킬 사용
		cout << "스킬을 사용합니다." << '\n';
		break;
	case 3:
		cout << "아이템을 사용합니다." << '\n';
		// 아이템 사용 로직 추가 (예: 체력 회복, 공격력 증가 등)
		break;
	case 4:
		// 도망
		cout << "도망칩니다." << '\n';
		battleResult = BattleResult::RunAway;
		break;
	default:
		break;
	}


}

void BattleSystem::monsterAction(Player* player, Monster* monster) {

	cout << "*" << '\n';
	cout << "몬스터의 턴입니다!" << '\n';
	// 몬스터의 공격
	cout << monster->getName() << "이(가) " << player->getName() << " 대원을 공격합니다!" << '\n';
	player->takeDamage(monster->getAttack());

}

void BattleSystem::startBattleSequence(Player* player) {

	BattleResult battleResult;
	battleResult = battle(player);

	// 전투 끝
	player->useOxygen(10);

	cout << "==========================================================" << '\n';
	cout << "전투가 끝났습니다." << '\n';

	// 플레이어가 이겼을 때 보상 획득

	if (battleResult == BattleResult::PlayerWin) { //승리했을 때

		//보상 획득
		player->gainExp(50);

		// 골드 10~20 범위에서 랜덤 획득
		int gold = random.getRandomValue(10, 20);
		player->addGold(gold);

		
			


		//아이템 획득
	}
	else if(battleResult == BattleResult::RunAway){
		cout << "무사히 도망쳤습니다." << '\n';
	}
	else if(battleResult == BattleResult::MonsterWin){
		cout << "대원이 쓰러졌습니다." << '\n';
	}

	cout << "==========================================================" << '\n';
}

void prize(Player* player) {

}
