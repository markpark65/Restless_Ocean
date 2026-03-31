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
#include "GlobalVal.h"
using namespace std;



BattleSystem::BattleSystem()
{
	turn = 1;
	player = &GameManager::getInstance().getPlayer();

}

BattleResult BattleSystem::startBattleSequence(Player* p, AttributeType mapType)
{
	// 1. 무기 선택 (전투 시작 전 한 번만)
	//player = p;
	//player->setWeapon(weaponManager.selectWeapon());
	//cout << '\n';

	BattleResult battleResult = battle(mapType); // 실제 전투 발생

	// 결과 처리 (승리/패배/도망 등)
	processBattleResult(battleResult);

	return battleResult;
}



BattleResult BattleSystem::battle(AttributeType mapType)
{
	g_sceneData.description = "탐색중...";
	g_cliRenderer.render(g_sceneData);
	this_thread::sleep_for(chrono::seconds(2));

	// 전투 턴 수
	MonsterFactory monsterFactory;
	monster.reset(monsterFactory.GenerateMonster(
		player->getLevel(),
		GameManager::getInstance().getBattleCount(),
		mapType
	));
	//cout << "===============================" << '\n';
	//cout << monster->getName() << "이(가) 나타났습니다!" << '\n';
	g_sceneData.description = monster->getName() + "이(가) 나타났습니다!";

	//uniqueptr.get()을 통해 읽기전용 raw포인터를 가져올 수 있음.
	g_sceneData.monster = monster.get();
	g_cliRenderer.render(g_sceneData);
	//monster->showStat();
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

	return battleResult;
}


bool BattleSystem::processBattleResult(BattleResult& battleResult)
{
	// 전투 끝 로직 
	//cout << "==========================================================" << '\n';
	//cout << "전투가 끝났습니다." << '\n';

	g_sceneData.description = "전투가 끝났습니다. \n ";
	g_sceneData.monster = nullptr;
	player->useOxygen(10); // 전투 후 산소 10 소모
	player->takePressure(10); // [추가] 전투당 압력 10 증가
	player->resetTempStats(); // 전투후 추가 공격력 초기화
	if (battleResult == BattleResult::PlayerWin)
	{
		// 배틀 횟수 증가
		GameManager::getInstance().increaseBattleCount();
		//승리했을 때
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
		g_sceneData.description = "무사히 도망쳤습니다. \n ";
		//cout << "무사히 도망쳤습니다." << '\n';
		return false;
	}
	else if (battleResult == BattleResult::MonsterWin)
	{ // 졌을 때
		//cout << "대원이 쓰러졌습니다." << '\n';
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
	else if(playerHp <= 0)
	{
		return BattleResult::MonsterWin;
	}
	return BattleResult::Continue;
}

void BattleSystem::playerAction(int turn, BattleResult& battleResult)
{
	//cout << "* 플레이어의 턴입니다!" << '\n';
	g_sceneData.description = "* 플레이어의 턴입니다! \n ";

	g_sceneData.sceneText = {};
	//player->showStatus(); // 플레이어 상태 출력
	//cout << '\n';

	bool actionCompleted = false;
	//cout << "1. 일반 공격"	<< '\n';
	//cout << "2. 스킬 사용"	<< '\n';
	//cout << "3. 아이템 사용" << '\n';
	//cout << "4. 도망치기"	<< '\n';


	while (!actionCompleted)
	{
		g_sceneData.sceneText = {};
		g_sceneData.selectedIndex = 0;
		g_sceneData.options = {
			"1. 일반 공격",
			"2. 스킬 사용",
			"3. 아이템 사용",
			"4. 도망치기"
		};
		int selectedIndex = g_cliRenderer.OptionSelector(g_sceneData);
		switch (selectedIndex)
		{
		case 0:
			playerAttack(turn);
			actionCompleted = true;
			break;
		case 1:
			actionCompleted = playerUseSkill();
			break;
		case 2:
			actionCompleted = playerUseItem();
			break;
		case 3:
			// 도망
			playerRunAway(battleResult);
			actionCompleted = true;
			break;
		default:
			break;
		}
	}
}

int BattleSystem::selectAction()// 행동 선택 함수
{
	//UI적용후 미사용
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
	//cout << "* " << attackDamage << "의 피해를 " << monster->getName() << "에게 입힙니다!" << '\n';
	g_sceneData.description += "* " + std::to_string(attackDamage) + "의 피해를 " + monster->getName() + "에게 입힙니다! \n ";
	monster->takeDamage(attackDamage);

	g_cliRenderer.render(g_sceneData);
	this_thread::sleep_for(chrono::seconds(2));
}

bool BattleSystem::playerUseSkill() // 플레이어 스킬 사용 함수
{
	//cout << "* 스킬을 사용합니다." << '\n';
	g_sceneData.description += "*스킬을 사용합니다. \n ";
	bool skillSuccess = player->useSkill(monster.get());
	if (skillSuccess)
	{
		g_cliRenderer.render(g_sceneData);
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
	g_sceneData.description = "보유중인 아이템 \n ";
	g_sceneData.sceneText = {};
	g_sceneData.sceneText.push_back("=== 보유 아이템 목록 === ");
	g_sceneData.sceneText.push_back("0: [이전으로 돌아가기]");
	g_sceneData.selectedIndex = 0;
	g_sceneData.options = { "이전으로 돌아가기" };
	//std::cout << "\n=== 판매 ===\n";
	//std::cout << "0: [상점으로 돌아가기]\n\n";
	int size = player->getInventory().getSize();

	if (player->getInventory().getSize() == 0) {
		g_sceneData.description = "보유한 아이템이 없습니다. \n ";
		return false;
	}

	std::vector<std::string> items = player->getInventory().printAllstr();
	for (auto& it : items) {
		g_sceneData.sceneText.push_back(it);
		//g_sceneData.options.push_back(it);
	}
	for (int i = 0; i < player->getInventory().getSize(); i++) {
		Item* item = player->getInventory().getItem(i);
		//g_sceneData.sceneText.push_back(item->tostring());
		std::string name = item->getName();

		//이름이너무길어
		if (name == "방수가 잘 되어있는 초코과자")
			name = "초코과자";
		g_sceneData.options.push_back(name);
	}
	g_sceneData.description += "사용할 아이템 선택 \n ";
	g_cliRenderer.render(g_sceneData);
	//std::cout << "사용할 아이템 선택 ";
	int input = g_cliRenderer.OptionSelector(g_sceneData);


	//cout << "아이템을 선택하세요." << '\n';
	//int itemIndex = player->getInventory().selectItem();
	
	if (input != 0) // 올바른 아이템 인덱스
	{
		player->getInventory().useItem(input-1, player);
		g_cliRenderer.render(g_sceneData);
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
	g_sceneData.description += "* 도망칩니다. \n ";
	//cout << "* 도망칩니다." << '\n';

	g_cliRenderer.render(g_sceneData);
	this_thread::sleep_for(chrono::seconds(2));
}

void BattleSystem::monsterAction(int turn)
{
	g_sceneData.description = "* 몬스터의 턴입니다! \n ";
	g_sceneData.sceneText = {};
	//cout << "* 몬스터의 턴입니다!" << '\n';

	//monster->showStat();

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
	

	//cout << '\n';
	g_cliRenderer.render(g_sceneData);
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
		g_cliRenderer.render(g_sceneData);
		this_thread::sleep_for(chrono::seconds(1));

		// 골드 10~20 범위에서 랜덤 획득
		gold = random.getRandomValue(10, 20);
		player->addGold(gold);
		g_cliRenderer.render(g_sceneData);
		this_thread::sleep_for(chrono::seconds(1));

		// 30% 확률로 아이템 획득
		int itemChance = random.getRandomValue(1, 100);

		if (itemChance <= 30)
		{
			//cout << "아이템을 획득했습니다!" << '\n';

			Item* obtainedItem = itemFactory.getRandomItem();
			GameLogger::getInstance().log(EventType::ObtainItem, player->getName(), obtainedItem->getName());
			GameLogger::getInstance().printRecentLog();
			player->getInventory().addItem(obtainedItem);
		}

	}
	g_cliRenderer.render(g_sceneData);
	this_thread::sleep_for(chrono::seconds(1));

}
