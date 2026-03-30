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
	player = &GameManager::getInstance().getPlayer();

}

BattleResult BattleSystem::startBattleSequence(Player* p, AttributeType mapType)
{
	// 1. 무기 선택 (전투 시작 전 한 번만)
	//player = p;
	//player->setWeapon(weaponManager.selectWeapon());
	//cout << '\n';
	/*std::unique_ptr<Weapon> selectedWeapon = weaponManager.selectWeapon();
	if (selectedWeapon) {
		player->setWeapon(std::move(selectedWeapon));
	}*/
	BattleResult battleResult = battle(mapType); // 실제 전투 발생

	// 결과 처리 (승리/패배/도망 등)
	processBattleResult(battleResult);

	return battleResult;
}



BattleResult BattleSystem::battle(AttributeType mapType)
{
	// 전투 턴 수
	MonsterFactory monsterFactory;
	monster.reset(monsterFactory.GenerateMonster(
		player->getLevel(),
		GameManager::getInstance().getBattleCount(),
		mapType
	));

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
			playerAction(battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			monsterAction();
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
		}
		else
		{
			// 몬스터가 먼저 행동
			monsterAction();
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

			playerAction(battleResult);
			if (battleResult != BattleResult::Continue) break;
			battleResult = checkBattleStatus(player->getHp(), monster->getHealth());
			if (battleResult != BattleResult::Continue) break;

		}

	}

	return battleResult;
}


bool BattleSystem::processBattleResult(BattleResult& battleResult)
{
	// 전투 끝 로직 
	cout << "==========================================================" << '\n';
	cout << "전투가 끝났습니다." << '\n';
	player->useOxygen(10); // 전투 후 산소 10 소모
	player->takePressure(10); // [추가] 전투당 압력 10 증가
	player->resetTempStats(); // 전투후 추가 공격력 초기화
	if (battleResult == BattleResult::PlayerWin)
	{
		// 배틀 횟수 증가
		GameManager::getInstance().increaseBattleCount();
		//승리했을 때

		// Kill 로그 출력
		GameLogger::getInstance().log(EventType::Kill, player->getName(), monster->getName());
		GameLogger::getInstance().printRecentLog();
		prize();

		// 유적 3곳을 모두 발견했을 때
		if (player->hasAllArtifacts())
		{
			GameManager::getInstance().setIsPlayerExit(false);
			GameManager::getInstance().endGame(GameOverReason::Clear);
			return false;
		}


		return true;
	}
	else if (battleResult == BattleResult::RunAway)
	{ // 도망쳤을 때
		// 복귀 로그 출력
		GameLogger::getInstance().log(EventType::Return, player->getName());
		GameLogger::getInstance().printRecentLog();

		
		return false;
	}
	else if (battleResult == BattleResult::PlayerLose)
	{ // 졌을 때
		// 패배 로그 출력
		GameLogger::getInstance().log(EventType::Death, player->getName(), monster->getName());
		GameLogger::getInstance().printRecentLog();

		GameManager::getInstance().setIsPlayerExit(false);
		GameManager::getInstance().endGame(GameOverReason::Die);
		return false;
	}
	return false;
}

BattleResult BattleSystem::checkBattleStatus(int playerHp, int monsterHp)
{
	if (monsterHp <= 0)
	{
		return BattleResult::PlayerWin;
	}
	else if (playerHp <= 0)
	{
		return BattleResult::PlayerLose;
	}
	return BattleResult::Continue;
}

void BattleSystem::playerAction(BattleResult& battleResult)
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
			playerAttack();
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

void BattleSystem::playerAttack() // 플레이어 일반 공격 함수
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

void BattleSystem::monsterAction()
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
		if (itemChance <= 50)
		{
			
			Item* obtainedItem = itemFactory.getRandomItem();

			//아이템 획득 로그 출력
			GameLogger::getInstance().log(EventType::ObtainItem, player->getName(), obtainedItem->getName());
			GameLogger::getInstance().printRecentLog();

			player->getInventory().addItem(obtainedItem);
		}

	}
	this_thread::sleep_for(chrono::seconds(1));

}
