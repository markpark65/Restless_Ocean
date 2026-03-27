#pragma once

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
	void battle(Player* player); // 전투 로직
	void startBattleSequence(Player* player); // 전투-보상 시퀀스 ( 나중에 보상 시퀀스 따로 구현)

	void playerAction(Player* player, Monster* monster, BattleResult& battleResult); // 플레이어 행동 함수
	void monsterAction(Player* player, Monster* monster); // 몬스터 행동 함수
	BattleResult checkBattleResult(int playerHp, int monsterHp); // 배틀이 끝났는지 확인하는 함수

	//void displayInventory(Player* player);
};

