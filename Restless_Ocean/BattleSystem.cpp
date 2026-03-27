#include <thread>
#include <chrono>
#include "BattleSystem.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "GameLogger.h"
#include "Random.h"
#include "InputSystem.h"
using namespace std;

GameLogger& logger = GameLogger::getInstance(); // 모든 로그 나중에 GameLogger 활용 로직으로 변경 예정
Random random;


void BattleSystem::startBattleSequence(Player* player)
{


	
	// 일반 전투
	for (int i = 0; i < 7; ++i)
	{
		cout << "================================" << '\n';
		cout << i + 1 << "번째 전투" << '\n';
		BattleResult battleResult;
		battleResult = battle(player);

		bool canContinue = processBattleResult(player, battleResult);
		if (!canContinue)
		{
			break;
		}
	}
	cout << "================================" << '\n';

	// 보스전

}



BattleResult BattleSystem::battle(Player* player)
{
	int turn = 0; // 전투 턴 수
	MonsterFactory monsterFactory;
	Monster* monster = monsterFactory.GenerateMonster(player->getLevel());

	this_thread::sleep_for(chrono::seconds(2));

	cout << "===============================" << '\n';
	cout << monster->getName() << "이(가) 나타났습니다!" << '\n';
	monster->showStat();
	this_thread::sleep_for(chrono::seconds(2));


	// 전투 시작
	BattleResult battleResult = BattleResult::Continue;

	while (battleResult == BattleResult::Continue)
	{
		
		if (player->getSpeed() >= monster->getSpeed())
		{
			// 플레이어가 먼저 행동
			playerAction(turn, player, monster, battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			monsterAction(turn, player, monster);
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
		}
		else
		{
			// 몬스터가 먼저 행동
			monsterAction(turn, player, monster);
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			playerAction(turn, player, monster, battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

		}
		
	}

	delete monster;
	return battleResult;
}


bool BattleSystem::processBattleResult(Player* player, BattleResult& battleResult)
{
	// 전투 끝 로직 
	cout << "==========================================================" << '\n';
	cout << "전투가 끝났습니다." << '\n';
	player->useOxygen(10); // 전투 후 산소 10 소모

	if (battleResult == BattleResult::PlayerWin)
	{ //승리했을 때
		prize(player);
		return true;
	}
	else if (battleResult == BattleResult::RunAway)
	{ // 도망쳤을 때
		cout << "무사히 도망쳤습니다." << '\n';
		return false;
	}
	else if (battleResult == BattleResult::MonsterWin)
	{ // 졌을 때
		cout << "대원이 쓰러졌습니다." << '\n';
		return false;
	}
}

BattleResult BattleSystem::checkBattleStatus(int playerHp, int monsterHp)
{
	if (monsterHp <= 0)
	{
		return BattleResult::PlayerWin;
	}
	else if(playerHp <= 0)
	{
		return BattleResult::MonsterWin;
	}
	return BattleResult::Continue;
}

void BattleSystem::playerAction(int& turn, Player* player, Monster* monster, BattleResult& battleResult)
{
	cout << "* 플레이어의 턴입니다!" << '\n';

	player->showStatus(); // 플레이어 상태 출력
	cout << '\n';

	// 플레이어 행동 선택
	int choice = 0;
	cout << "1. 일반 공격" << '\n';
	cout << "2. 스킬 사용" << '\n';
	cout << "3. 아이템 사용" << '\n';
	cout << "4. 도망치기" << '\n';

	InputSystem inputSystem;
	cout << "행동을 선택하세요: ";
	choice = inputSystem.getInputInt(1, 4);
	cout << '\n';

	switch (choice)
	{
	case 1:
		playerAttack(turn, player, monster);
		break;
	case 2:
		playerUseSkill(player, monster);
		break;
	case 3:
		playerUseItem(player);
		break;
	case 4:
		// 도망
		playerRunAway(battleResult);
		break;
	default:
		break;
	}
	cout << '\n';

}

void BattleSystem::playerAttack(int& turn, Player* player, Monster* monster) // 플레이어 일반 공격 함수
{
	cout << "* " << player->getAttack() << "의 피해를 " << monster->getName() << "에게 입힙니다!" << '\n';

	monster->takeDamage(player->getAttack());

	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::playerUseSkill(Player* player, Monster* monster) // 플레이어 스킬 사용 함수
{
	cout << "* 스킬을 사용합니다." << '\n';
	player->useSkill(monster);
	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::playerUseItem(Player* player) // 플레이어 아이템 사용 함수
{
	cout << "* 아이템을 사용합니다." << '\n';
	player->useItem("Health Potion"); // 예시로 체력 회복 아이템 사용, 실제로는 인벤토리에서 선택하도록 구현 필요
	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::playerRunAway(BattleResult& battleResult)
{
	battleResult = BattleResult::RunAway;
	cout << "* 도망칩니다." << '\n';

	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::monsterAction(int& turn, Player* player, Monster* monster)
{
	cout << "* 몬스터의 턴입니다!" << '\n';

	//몬스터의 공격
	cout << monster->getName() << "이(가) " << player->getName() << " 대원을 공격합니다!" << '\n';
	player->takeDamage(monster->getAttack());

	cout << '\n';
	this_thread::sleep_for(chrono::seconds(2));

}

void BattleSystem::prize(Player* player)
{
	//보상 획득
	player->gainExp(50);
	this_thread::sleep_for(chrono::seconds(1));

	// 골드 10~20 범위에서 랜덤 획득
	int gold = random.getRandomValue(10, 20);
	player->addGold(gold);
	this_thread::sleep_for(chrono::seconds(1));

	// 30% 확률로 아이템 획득
	int itemChance = random.getRandomValue(1, 100);
	if (itemChance <= 30)
	{
		cout << "아이템을 획득했습니다!" << '\n';
		//아이템 획득 로직 추가 (예: 체력 회복 아이템, 공격력 증가 아이템 등)
	}
	this_thread::sleep_for(chrono::seconds(1));

}
