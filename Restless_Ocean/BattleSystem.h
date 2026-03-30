#pragma once
#include "Monster.h"
#include "ItemFactory.h"
#include "WeaponManager.h"

class Player;

enum class BattleResult {
	Continue, // 전투 계속
	PlayerWin, // 플레이어 승리
	PlayerLose, // 플레이어 패배
	RunAway // 도망
};

class BattleSystem
{
public:
	BattleSystem();

	// 배틀 흐름 관리
	BattleResult startBattleSequence(Player* player, AttributeType mapType); // 전투 흐름 전체 로직
	BattleResult battle(AttributeType mapType); // 턴제 전투 파트
	bool processBattleResult(BattleResult& battleResult); // 전투 결과 처리 함수
	BattleResult checkBattleStatus(int playerHp, int monsterHp); // 배틀이 끝났는지 확인하는 함수

	// 행동
	int selectAction(); // 행동 선택 함수
	void playerAction(BattleResult& battleResult); // 플레이어 행동 함수
	void monsterAction(); // 몬스터 행동 함수

	// 플레이어 행동(세부)
	void playerAttack(); // 플레이어 일반 공격 함수
	bool playerUseSkill(); // 플레이어 스킬 사용 함수
	bool playerUseItem(); // 플레이어 아이템 사용 함수
	void playerRunAway(BattleResult& battleResult); // 플레이어 도망 함수
	
	// 보상 관련 함수
	void prize(); // 전투 승리 시 보상 지급 함수
	//void displayInventory(Player* player);
private:
	unique_ptr<Monster> monster;
	Player* player;

	//WeaponManager weaponManager;
	ItemFactory itemFactory;

	
};

