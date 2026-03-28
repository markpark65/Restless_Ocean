#include <thread>
#include <chrono>
#include "BattleSystem.h"
#include "Player.h"
#include "MonsterFactory.h"
#include "GameLogger.h"
#include "Random.h"
#include "InputSystem.h"
#include "ItemFactory.h"
#include "WeaponManager.h"
#include "GameManager.h"
using namespace std;



BattleSystem::BattleSystem()
{
	turn = 1;
	player = &GameManager::getInstance().getPlayer();

}

void BattleSystem::startBattleSequence(Player* p)
{
	// 무기 선택
	player = p;
	player->setWeapon(weaponManager.selectWeapon());
	cout << '\n';
	
	// 일반 전투
	for (int i = 0; i < 100; ++i)
	{
		cout << "================================" << '\n';
		cout << i + 1 << "번째 전투" << '\n';
		BattleResult battleResult;

		battleResult = battle();

		bool canContinue = processBattleResult(battleResult);
		if (!canContinue)
		{
			break;
		}
		GameManager::getInstance().increaseBattleCount();
	}
	cout << "================================" << '\n';


}



BattleResult BattleSystem::battle()
{
	// 전투 턴 수
	MonsterFactory monsterFactory;
	monster.reset(monsterFactory.GenerateMonster(player->getLevel(), GameManager::getInstance().getBattleCount()));

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
			playerAction(getTurnCount(), battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			monsterAction(turn);
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
		}
		else
		{
			// 몬스터가 먼저 행동
			monsterAction(turn);
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			playerAction(turn, battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

		}
		
	}

	// 배틀 횟수 카운트 증가
	GameManager::getInstance().increaseBattleCount();

	
	return battleResult;
}


bool BattleSystem::processBattleResult(BattleResult& battleResult)
{
	// 전투 끝 로직 
	cout << "==========================================================" << '\n';
	cout << "전투가 끝났습니다." << '\n';
	player->useOxygen(10); // 전투 후 산소 10 소모

	if (battleResult == BattleResult::PlayerWin)
	{
		// 유적 3곳을 모두 발견했을 때
		if (player->hasAllArtifacts())
		{
			GameManager::getInstance().setIsPlayerExit(false);
			GameManager::getInstance().endGame(GameOverReason::Clear);
			return false;
		}

		//승리했을 때
		prize();
		return true;
	}
	else if (battleResult == BattleResult::RunAway)
	{ // 도망쳤을 때
		cout << "무사히 도망쳤습니다." << '\n';
		return false;
	}
	else if (battleResult == BattleResult::MonsterWin)
	{ // 졌을 때
		//cout << "대원이 쓰러졌습니다." << '\n';
		GameManager::getInstance().setIsPlayerExit(false);
		GameManager::getInstance().endGame(GameOverReason::Die);
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

void BattleSystem::playerAction(int turn, BattleResult& battleResult)
{
	cout << "* 플레이어의 턴입니다!" << '\n';

	player->showStatus(); // 플레이어 상태 출력
	cout << '\n';

	bool actionCompleted = false;

	while (!actionCompleted)
	{
		// 플레이어 행동 선택
		int choice = selectAction();
		switch (choice)
		{
		case 1:
			playerAttack(turn);
			actionCompleted = true;
			break;
		case 2:
			actionCompleted = playerUseSkill();
			break;
		case 3:
			actionCompleted = playerUseItem();
			break;
		case 4:
			// 도망
			playerRunAway(battleResult);
			actionCompleted = true;
			break;
		default:
			break;
		}
		cout << '\n';
	}


}

int BattleSystem::selectAction()// 행동 선택 함수
{
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
	return choice;
}

void BattleSystem::playerAttack(int turn) // 플레이어 일반 공격 함수
{
	int attackDamage = player->attack(monster.get());
	cout << "* " << attackDamage << "의 피해를 " << monster->getName() << "에게 입힙니다!" << '\n';
	monster->takeDamage(attackDamage);

	this_thread::sleep_for(chrono::seconds(2));
}

bool BattleSystem::playerUseSkill() // 플레이어 스킬 사용 함수
{
	cout << "* 스킬을 사용합니다." << '\n';

	bool skillSuccess = player->useSkill(monster.get());
	if (skillSuccess)
	{
		this_thread::sleep_for(chrono::seconds(2));
		return true;
	}
	else
	{
		return false;
	}
	
}

bool BattleSystem::playerUseItem() // 플레이어 아이템 사용 함수
{
	cout << "아이템을 선택하세요." << '\n';
	int itemIndex = player->getInventory().selectItem();
	
	if (itemIndex != -1) // 올바른 아이템 인덱스
	{
		player->getInventory().useItem(itemIndex, player);
		this_thread::sleep_for(chrono::seconds(2));
		return true;
	}
	else // 아이템 사용 불가
	{
		return false;
	}
}

void BattleSystem::playerRunAway(BattleResult& battleResult)
{
	battleResult = BattleResult::RunAway;
	cout << "* 도망칩니다." << '\n';

	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::monsterAction(int turn)
{
	cout << "* 몬스터의 턴입니다!" << '\n';

	monster->showStat();

	// 패시브 발동
	monster->activatePassive();

	// 일반 공격 or 특수 공격
	int attackType = Random::getRandomValue(0, 100);
	
	if (attackType <= 50)
	{
		monster->useBasicAttack(player);
	}
	else
	{
		monster->useSpecialAttack(player);
	}
	

	cout << '\n';
	this_thread::sleep_for(chrono::seconds(2));

}

void BattleSystem::prize()
{
	Random random;
	int gold = 0;


	if (monster->getRank() == BossRank::Boss) // 보스 몬스터 보상
	{
		player->gainExp(100);
		gold = random.getRandomValue(20, 40);
		player->addArtifact(monster->getRewardArtifact());
	}
	else // 일반 몬스터 보상
	{
		//보상 획득
		player->gainExp(50);
		this_thread::sleep_for(chrono::seconds(1));

		// 골드 10~20 범위에서 랜덤 획득
		gold = random.getRandomValue(10, 20);
		player->addGold(gold);
		this_thread::sleep_for(chrono::seconds(1));

		// 30% 확률로 아이템 획득
		int itemChance = random.getRandomValue(1, 100);

		if (itemChance <= 30)
		{
			cout << "아이템을 획득했습니다!" << '\n';

			//아이템 획득 로직 추가 (예: 체력 회복 아이템, 공격력 증가 아이템 등)
			player->getInventory().addItem(itemFactory.getRandomItem());
		}

	}
	this_thread::sleep_for(chrono::seconds(1));

}
