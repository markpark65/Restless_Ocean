#pragma once
#include "ItemFactory.h"
#include "WeaponManager.h"

class Monster;
class Player;


enum class BattleResult {
	Continue, // 전투 계속
	PlayerWin, // 플레이어 승리
	MonsterWin, // 몬스터 승리
	RunAway // 도망
};

class BattleSystem
{
public:
	static int battleCount;
	BattleSystem();

	// 전체 흐름 관리 함수
	void startBattleSequence(Player* player); // 전투 흐름 전체 로직
	BattleResult battle(Player* player); // 턴제 전투 파트
	bool processBattleResult(Player* player, BattleResult& battleResult); // 전투 결과 처리 함수

	// 행동 관련 함수
	int selectAction(); // 행동 선택 함수
	void playerAction(int& turn, Player* player, Monster* monster, BattleResult& battleResult); // 플레이어 행동 함수
	void monsterAction(int& turn, Player* player, Monster* monster); // 몬스터 행동 함수

	void playerAttack(int& turn, Player* player, Monster* monster); // 플레이어 일반 공격 함수
	void playerUseSkill(Player* player, Monster* monster); // 플레이어 스킬 사용 함수
	bool playerUseItem(Player* player); // 플레이어 아이템 사용 함수
	void playerRunAway(BattleResult& battleResult); // 플레이어 도망 함수

	BattleResult checkBattleStatus(int playerHp, int monsterHp); // 배틀이 끝났는지 확인하는 함수

	
	// 보상 관련 함수
	void prize(Player* player); // 전투 승리 시 보상 지급 함수
	//void displayInventory(Player* player);
private:
	/*Monster* monster;
	BattleResult battleResult;
	Random random;*/
	WeaponManager weaponManager;
	ItemFactory itemFactory;
};

